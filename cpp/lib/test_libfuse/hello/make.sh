gcc -Wall hello.c `pkg-config fuse3 --cflags --libs` -o hello

# 编译成功后能看到生成的可执行文件 hello
# 建立一个挂载点 /tmp/fuse
# 运行 ./hello /tmp/fuse
# 运行 ll /tmp/fuse 可看到一个 hello 文件
# 运行 cat /tmp/fuse/hello 可以看到显示 Hello World!
# 调试时加上”-d“可以看到FUSE和自己的调试输出
