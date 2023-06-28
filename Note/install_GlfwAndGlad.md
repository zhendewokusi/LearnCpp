###Linux安装glfw3以及glad库

##安装Glfw3库

我使用的是Archlinux + X11直接使用pacman进行下载

sudo pacman -S glfw-x11

这儿有三个选项:
glfw-wayland:如果是wayland则下载这个
glfw-doc:GLFW-doc 只是 GLFW 的文档，提供了 GLFW 库的详细信息和使用说明。GLFW-doc 不包含任何代码或库文件，它主要用于帮助开发人员更好地理解和使用 GLFW。

查看自己的窗口系统

echo $XDG_SESSION_TYPE

显示是X11就是下载X11,反之亦然

##安装Glad头文件以及动态库

首先从Github上下载对应的库
git clone https://github.com/Dav1dde/glad.git
下载完进入对应目录
cd glad
新建一个分支,防止出现意外
git checkout son
使用gcc编译glad.c,-fpic 选项指定了生成位置独立代码的方式,-c选项指定了编译器只编译源文件而不进行链接。这将生成一个目标文件.
gcc -fpic src/glad.c -c
这一步如果报错没有找到glad.h文件:
查找你本地的glad.h文件路径
find / -name glad.h 2>/dev/null
/home/yuanfang/miscellaneous/glad/include/glad/glad.h
下面的-I参数后面不要加空格!且复制上面输出的路径到include就行(让编译器找到glad.h文件).
gcc -I/home/yuanfang/miscellaneous/glad/include/ src/glad.c -fpic -c
gcc编译器将 glad.o 目标文件链接为一个libglad.so的共享库文件
gcc -shared -Wl,-z,relro,-z,now -o libglad.so glad.o
将共享库放置在共享库目录,以便其他程序(eg:vscode)能正常使用
sudo cp libglad.so /usr/lib/
将头文件放置在默认的头文件目录中
sudo cp include/* -r /usr/include
