/* 
 * minimal example filesystem using high-level API
 *
 * Compile with:
 *     gcc -Wall hello.c `pkg-config fuse3 --cflags --libs` -o hello
 *
 */


#define FUSE_USE_VERSION 31

#include <fuse3/fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <assert.h>

static struct options {
    const char *filename;
    const char *contents;
    int show_help;
} options;

#define OPTION(t, p) \
    { t, offsetof(struct options, p), 1 }

    //{"--name=%s", offsetof(struct options, filename), 1 }
static const struct fuse_opt option_spec[] = {
    OPTION("--name=%s", filename),
    OPTION("--contents=%s", contents),
    OPTION("-h", show_help),
    OPTION("--help", show_help),
    FUSE_OPT_END
};

static void *hello_init(struct fuse_conn_info *conn, 
                        struct fuse_config *cfg) {
    (void) conn;
    cfg->kernel_cache = 1;
    return NULL;
}

/* 与函数stat()类似，用于得到文件属性，并将其存入结构体
 * struct stat* stbuf 当中 */
static int hello_getattr(const char *path, struct stat *stbuf, 
                         struct fuse_file_info *fi) {
    (void) fi;
    int res = 0;

    memset(stbuf, 0, sizeof(struct stat)); // 使用memset初始化结构体
    if(strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755; // S_IFDIR 说明 / 为目录
        stbuf->st_nlink = 2; // 设置文件存在的硬链接数
    }else if(strcmp(path+1, options.filename) == 0) { // path指针+1，取hello（去掉/）
        stbuf->st_mode = S_IFREG | 0444; //S_IFREG 说明 /hello 为常规文件
        stbuf->st_nlink = 1; // 设置文件存在的硬链接数
        stbuf->st_size = strlen(options.contents); // 设置文件长度
    }else {
        res = -ENOENT;
    }
    return res; // 成功返回0
}

// 此函数用于读取目录内容，并在 / 目录下增加 . .. hello 这三个目录项
static int hello_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                         off_t offset, struct fuse_file_info *fi,
                         enum fuse_readdir_flags flags) {
    (void) offset;
    (void) fi;
    (void) flags;

    if (strcmp(path, "/") != 0) {
        return -ENOENT;
    }

    /* filler() 的作用是在 readdir() 中增加一个目录项
     * typedef int (*fuse_fill_dir_t) (void* buf, const char* name, 
     *                                 const struct stat* stbuf, off_t off);
     */
    filler(buf, ".", NULL, 0, 0);
    filler(buf, "..", NULL, 0, 0);
    filler(buf, options.filename, NULL, 0, 0);

    return 0;
}

// 打开文件函数
static int hello_open(const char *path, struct fuse_file_info *fi) {
    if (strcmp(path+1, options.filename) != 0) {
        return -ENOENT;
    }
    if ((fi->flags & O_ACCMODE) != O_RDONLY) {
        return -EACCES;
    }
    return 0;
}

// 读文件
static int hello_read(const char *path, char *buf, size_t size, off_t offset,
                      struct fuse_file_info *fi) {
    size_t len;
    (void) fi;
    if(strcmp(path+1, options.filename) != 0) {
        return -ENOENT;
    }
    len = strlen(options.contents);
    if(offset < len) {
        if (offset + size > len) {
            size = len - offset;
        }
        memcpy(buf, options.contents + offset, size);
    }else {
        size = 0;
    }
    return size;
}

// 注册自定义函数
static struct fuse_operations hello_oper = {
    .init       = hello_init,
    .getattr    = hello_getattr,
    .readdir    = hello_readdir,
    .open       = hello_open,
    .read       = hello_read,
};

int main(int argc, char *argv[]) {
    options.filename = strdup("helloT");
    options.contents = strdup("Hello tmp!\n");
    // 调用fuse_main，把控制权交给fuse
    return fuse_main(argc, argv, &hello_oper, NULL);
}
