#define FUSE_USE_VERSION 32
 
#include <stdio.h>
#include <sys/xattr.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <fuse3/fuse.h>

#define CHECK \
    if(!file_manager::instance()->check(path)){ \
        return -ENOENT; \
    }

static int t_getattr(const char* path, struct stat* stbuf, struct fuse_file_info *fi){
    fprintf(stderr, "*******t_getattr, path:[%s], fuse_file_info[%lu], fi->fh[%lu]\n", path, (uint64_t)fi, (fi==NULL)?9999:fi->fh);
    return 0;
}

static int t_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    fprintf(stderr, "*******t_read, path:[%s], fi[%lu], fi->fh[%lu], size:%d, offset:%d\n", path, (uint64_t)fi, fi->fh, (int)size, (int)offset);
    return 0;
}

int t_getxattr(const char *path, const char *, char *, size_t){
    return 0;
}

static std::string get_exe_path(){
    std::string re = "";
    char exe_full_path[1024] = {0};
    char *last_slash = NULL;
    char exe_path[1024] = {0};

    // exe_path
    if(readlink("/proc/self/exe", exe_full_path,1024) <=0){
        fprintf(stderr, "error to get self path\n");
        return re;
    }  
    last_slash = strrchr(exe_full_path, '/');
    if(last_slash == NULL){
        fprintf(stderr, "error to find slash in exe_full_path\n");
        return re;
    }
    snprintf(exe_path,
        last_slash-exe_full_path+1,
        "%s",
        exe_full_path);
 
    re = std::string(exe_path);
    return re; 
}
fuse_operations _ops;

int main(int argc, char* argv[]){
    // mount dir
    std::string dir = get_exe_path();
    dir += "/dir/";
    char *mount_dir = getenv("yfuse_mount_dir");
    if(mount_dir != NULL){
        dir = std::string(mount_dir);
    }
    {// umount
        std::string cmd = "umount ";
        cmd += dir;
        system(cmd.c_str());
    }
    rmkdir(dir.c_str());

    int count = 2;
    char *front = getenv("yfuse_front_run");
    if(front != NULL){
        std::string fronts(front);
        if(fronts == "1"){
            count = 3;
        }
    }

    char *arr[3] = {argv[0], "-d", (char*)dir.c_str()};
    if(count == 2){
        arr[1] = (char*)dir.c_str();
    }

    //
    umask(0);
    _ops.getattr    = t_getattr;
    _ops.read       = t_read;
    _ops.open       = t_open;
    _ops.write      = t_write;
    _ops.truncate   = t_truncate;
    _ops.flush      = t_flush;
    _ops.getxattr   = t_getxattr;
    _ops.removexattr= t_removexattr;
    _ops.create     = t_create;
    _ops.readdir    = t_readdir;
    _ops.unlink     = t_unlink;
    _ops.fsync      = t_fsync;
    return fuse_main(count, arr, &_ops, NULL);
}






