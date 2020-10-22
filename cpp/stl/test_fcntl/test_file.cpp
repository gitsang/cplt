
/*
---------------------------------------------------------------------------------

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);

int creat(const char *pathname, mode_t mode);

int openat(int dirfd, const char *pathname, int flags);
int openat(int dirfd, const char *pathname, int flags, mode_t mode);

---------------------------------------------------------------------------------

#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
ssize_t read(int fd, void *buf, size_t count);

---------------------------------------------------------------------------------

list of file creation flags:
    O_APPEND
    O_ASYNC
    O_CLOEXEC
    O_CREAT
        S_IRWXU  00700 user (file owner) has read, write, and execute permission
        S_IRUSR  00400 user has read permission
        S_IWUSR  00200 user has write permission
        S_IXUSR  00100 user has execute permission
        S_IRWXG  00070 group has read, write, and execute permission
        S_IRGRP  00040 group has read permission
        S_IWGRP  00020 group has write permission
        S_IXGRP  00010 group has execute permission
        S_IRWXO  00007 others have read, write, and execute permission
        S_IROTH  00004 others have read permission
        S_IWOTH  00002 others have write permission
        S_IXOTH  00001 others have execute permission
        S_ISUID  0004000 set-user-ID bit
        S_ISGID  0002000 set-group-ID bit (see inode(7)).
        S_ISVTX  0001000 sticky bit (see inode(7)).
    O_DIRECT
    O_DIRECTORY
    O_DSYNC
    O_EXCL
    O_LARGEFILE
    O_NOATIME
    O_NOCTTY
    O_NOFOLLOW
    O_NONBLOCK or O_NDELAY
    O_PATH
    O_SYNC Write operations on the file will complete according to the
    O_TMPFILE
    O_TRUNC

---------------------------------------------------------------------------------
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>

#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>


int t_write(int argc, char** argv) {
    if(argc < 4) {
        fprintf(stderr, "usage: ./fopt write filename content\n");
        return -1;
    }

    int fd = open(argv[2], O_RDWR | O_CREAT);
    if(fd == -1) {
        fprintf(stderr, "open error");
        return -1; 
    }
    if(write(fd, argv[3], strlen(argv[3])) == -1) {
        fprintf(stderr, "write error"); 
        close(fd);
        return -1;
    }
    fprintf(stderr, "Write %d bytes to file \"%s\"\n", strlen(argv[3]), argv[2]);
    close(fd);
    return 0;
}

int t_read(int argc, char** argv) {
    if(argc < 4) {
        fprintf(stderr, "usage: ./fopt read filename readsize\n");
        return -1;
    }

    size_t count = std::stol(argv[3]);
    char* buf = (char*)malloc(count + 1);
    int fd = open(argv[2], O_RDWR);
    if(fd == -1) {
        fprintf(stderr, "open error");
        return -1;
    }
    int res = read(fd, buf, count);
    if(res == -1) {
        fprintf(stderr, "read error");
        close(fd);
        return -1;
    }
    fprintf(stderr, "Read %d bytes from file \"%s\"\n", res, argv[2]);
    fprintf(stderr, "%s\n", buf);
    close(fd);
    return 0;
}

int t_chmod(int argc, char* argv[]) {
    char* path = argv[2];
    mode_t mode = (mode_t)std::stol(argv[3]);

    return chmod(path, mode);
}
 
int main(int argc,char* argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Error! Usage:\n./fopt <filename> <content>\n");
        return -1;
    }
    if(!strcmp(argv[1], "write")) {
        return t_write(argc, argv);
    }else if(!strcmp(argv[1], "read")) {
        return t_read(argc, argv);
    }else if(!strcmp(argv[1], "chmod")) {
        return t_chmod(argc, argv);
    }else {
        fprintf(stderr, "usage: ./fopt <opt> <filename> <otheropt>\n"); 
    }


    return 0;
}

