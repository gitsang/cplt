/*
 * test va_list; vfprintf; vsprintf; vprintf;
 *
 * va_start(ap, v);
 *      va_start() 用于将 ap 指针指向可变参数的第一个参数位置
 *      ap 需传入 va_list 类型变量，v 用于指定可变参函数的第一个参数，通常用于指定可变参列表中参数的个数（或格式化字符串）
 *      必须调用 va_start() 传递有效的参数列表va_list和可变参函数的第一个参数
 * va_arg(ap, t);
 *      va_arg() 用于从 ap 中取下一个参数，其返回值为参数列表 ap 中的参数，返回参数类型为 t
 * va_end(ap);
 *      va_end() 用于将 ap 指针置空
 *
 * vprintf(format, vl);
 *      format 为格式化字符串，vl 为可变参数列表
 *      用于将可变参数列表以格式化方式输出
 *
 * vfprintf(stream, format, vl);
 *      stream 为 FILE* 类型，format 为格式化字符串，vl 为可变参数列表
 *      用于将可变参数列表以格式化方式输出到文件
 * 
 * vsprintf(buffer, format, vl);
 *      buffer 为 char* 类型，format 为格式化字符串，vl 为可变参数列表
 *      用于将可变参数列表以格式化方式输出到内存
 *
 * */

#include <stdio.h>
#include <stdarg.h>

void write_frm(FILE* stream, char* format, ...) {
    va_list vl;
    va_start(vl, format);
    vfprintf(stream, format, vl);
    va_end(vl);
}
void t_vfprintf() {
    FILE *fp;
    fp = fopen("file1","w");
    write_frm(fp, "3 argument %s %f %c\n", "aaa", 12.5, 'c', 1, 2, 3);
    fclose(fp);
}

void write_frm_2(char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
void t_vprintf() {
    write_frm_2("%d var arg\n", 1);
    write_frm_2("%d var %s\n", 2, "args");
}

void vspfunc(char* format, ...) {
    char buffer[50] = {0};
    va_list vl;
    va_start(vl, format);
    vsprintf(buffer, format, vl);
    printf("%s\n", buffer);
    va_end(vl);
}
void t_vsprintf() {
    int i = 5;
    float f =27.0;
    char str[50] = "test_vsprintf";
    vspfunc("%d %f %s", i, f, str);
}

int main () {
    t_vfprintf();
    t_vprintf();
    t_vsprintf();

    return 0;
}



