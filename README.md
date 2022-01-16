### 客户端服务端小软件
-------
个人笔记1：简单的一个客户端和服务端开发。

![image](https://user-images.githubusercontent.com/94120283/148217679-3f14dfb7-c99d-418e-bd14-5dfe1b156893.png)

**SOCKET**：

```c++
#include <sys/socket.h>
 int socket(int family,int type,int protocol); 　
 返回：非负描述字－－－成功　　　-1－－－失败
```
__第一个参数：__
协议簇
最常用的有AF_INET(IPv4协议)和AF_INET6(IPv6协议)；
__第二个参数：__
最常用的有AF_INET(IPv4协议)和AF_INET6(IPv6协议)
*流式套接字（SOCK_STREAM）*：
_流套接字用于提供面向连接、可靠的数据传输服务。该服务将保证数据能够实现无差错、无重复发送，并按顺序接收。流套接字之所以能够实现可靠的数据服务，原因在于其使用了传输控制协议，即TCP（The _Transmission Control Protocol）协议。

_数据包套接字（SOCK_DGRAM）:

数据包套接字提供了一种无连接的服务。该服务并不能保证数据传输的可靠性，数据有可能在传输过程中丢失或出现数据重复，且无法保证顺序地接收到数据。数据包套接字使用UDP（User Datagram Protocol）协议进行数据的传输。由于数据包套接字不能保证数据传输的可靠性，对于有可能出现的数据丢失情况，需要在程序中做相应的处理。

_原始套接字（SOCK_RAW）:
原始套接字(SOCKET_RAW)允许对较低层次的协议直接访问，比如IP、 ICMP协议，它常用于检验新的协议实现，或者访问现有服务中配置的新设备，因为RAW SOCKET可以自如地控制Windows下的多种协议，能够对网络底层的传输机制进行控制，所以可以应用原始套接字来操纵网络层和传输层应用。比如，我们可以通过RAW SOCKET来接收发向本机的ICMP、IGMP协议包，或者接收TCP/IP栈不能够处理的IP包，也可以用来发送一些自定包头或自定协议的IP包。网络监听技术很大程度上依赖于SOCKET_RAW

**Connect**：
可参考https://man7.org/linux/man-pages/man2/connect.2.html
```c++
#include <sys/socket.h>　　 　 　
  int connect(int sockfd, const struct sockaddr * addr, socklen_t addrlen); 　
 返回：0－－－成功　　　-1－－－失败
```
__第一个参数：__
socket函数返回的套接口描述字。

__第二个参数：__

socket地址指针

__第三个参数：__

该结构大小

**bind**：
在套接口中，一个套接字只是用户程序和内核交互的枢纽，没有啥信息，也没有网络地址和端口号，所以在通信时，必须将网络地址和端口号进行绑定，
可参考https://man7.org/linux/man-pages/man2/bind.2.html

```c++
#include <sys/socket.h> 　
 int bind(int sockfd, const struct sockaddr * server, socklen_t addrlen);
 返回：0－－－成功　　　-1－－－失败　
```
__第一个参数：__
socket函数返回的套接口描述字。

__第二个参数：__

socket地址指针

__第三个参数：__

该地址结构大小

**listen**：
监听套接字，仅被TCP服务器调用，将socket创建的主动套接口转化为 被动套接字，供客户端调用
参考https://man7.org/linux/man-pages/man2/listen.2.html
```c++
#include <sys/socket.h>
 int listen(int sockfd,int backlog); 　　
 返回：0－－－成功　　　-1－－－失败
```
__第一个参数：__

返回的套接字描述。

__第二个参数：__

在进程中接口最大连接数

内核需要维护两个队列，完成已完成和未完成的连接队列，未完成队列放置未TCP三次握手未完成队列，accept函数是从已经连接队列中去连接返回到进程。
进程为空时，则进程进入到睡眠状态。

**accept**：
accept函数由TCP服务调用，从已完成连接的队列中返回一个已完成连接，如果完成连接的队列为空则需进入

```c++
#include <sys/socket.h> 　　 　 　 　
 int accept(int listenfd, struct sockaddr *client, socklen_t * addrlen); 　
  回：非负描述字－－－成功　　　-1－－－失败
```
参考https://man7.org/linux/man-pages/man2/accept.2.html

__第一个参数：__

返回的套接字描述。

__第二个参数：__

在进程中接口最大连接数
客户端套接字地址结构

__第三个参数：__

该地址的长度

**write&read**：
当服务端和客户端建立起连接时，就可以进行写入和读取了，服务器和客户端用各自的套接字进行读/写操作，套接字是一种文件描述符号，所以可以用文件写读的函数进行读取和发送操作。

```c++
write()函数用于数据的发送。


#include <unistd.h> 　　 　 　 　
 int write(int sockfd, char *buf, int len);　
  回：非负－－－成功　　　-1－－－失败

```
在服务器中是accept()函数返回的已连接的套接字，对于客户端是调用socket（）函数返回的套接字。
buf是用于发送数据的缓冲区。

```c++
read()函数用于数据的读取。

#include <unistd.h> 　　 　 　 　
 int read(int sockfd, char *buf, intlen); 　
  回：非负－－－成功　　　-1－－－失败

```
在服务器中是accept()函数返回的已连接的套接字，对于客户端是调用socket（）函数返回的套接字。
buf是用于读取数据的缓冲区，len。












