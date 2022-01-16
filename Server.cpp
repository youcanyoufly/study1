// Server.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<Winsock2.h>
#include <iostream>
#include<windows.h>
using namespace std;

#pragma comment(lib,"WS2_32.lib")

int main()
{
    const int buffsize = 255;
    //std::cout << "Hello World!\n";
    char buf[buffsize];
    char sendbuf[buffsize];

    cout << "TCP Server:" << endl;
    WSADATA wsaData;//Wsa变量
    WORD wsaversion = MAKEWORD(2, 0);
    //指的是版本号，在socket编程中有例如MAKEWORD(1,0)||MAKEWORD(2,0)
    //调用的是不同的版本号，1.1仅仅支持TCP/IP协议，2.0版本可以支持到多种协议
     if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
         //初始化
        {
         cout << "WSAS初始化失败" << endl;
         return -1;
         }
     SOCKET SeverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
     //客户端socket
     SOCKET clientsocket;
     // int socket(int domain, int type, int protocol)
     // domain:
     // AF_INET:Address Family，指定TCP/IP协议家族
     // PF_INET:Protocol Family AF_INET和PF_INET应该是一个意思在Windows里
     // AF_UNIX：用于同一台计算机的进程间通信
     // AF_INET6:ipv6网络协议
     // type:
     // SOCK_STREAM:流套接字，对应TCP协议
     //SOCK_DGRAM:数据报套接字，对应UDP协议
     // SOCK_RAW : 原始套接字，提供原始网络协议存取
     //protocol:协议类型
     //传输层：IPPROTO_TCP、IPPROTO_UDP、IPPROTO_ICMP
     // 网络层：htons(ETH_P_IP | ETH_P_ARP | ETH_P_ALL)

     if (INVALID_SOCKET == SeverSocket)
     {
         cout << "socket failed!" << endl;
         WSACleanup();//释放套接字资源;
         return  -1;
     }

     sockaddr_in addr;//服务器地址
     addr.sin_family = AF_INET;
     addr.sin_port = htons(5000);
     addr.sin_addr.S_un.S_addr = INADDR_ANY;

     int remove;
     //绑定套接字
     remove=bind(SeverSocket, (sockaddr*)&addr, sizeof(addr));
     if (SOCKET_ERROR == remove)
     {
         cout << "绑定失败" << endl;
         closesocket(SeverSocket);
         WSACleanup();
         return -1;
     }
     cout << "socket true!" << endl;
     remove=listen(SeverSocket, 100);//最大监听数
     if (SOCKET_ERROR == remove)
     {
         cout << "监听失败" << endl;
         closesocket(SeverSocket);
         WSACleanup();
         return -1;

     }
     cout << "监听 true!" << endl;
     cout << "TCP Server is listening at 5000" << endl;

     //接受客户端的请求
     sockaddr_in addrclient;
   
     int clientlength = sizeof(addrclient);
 
   
         clientsocket = accept(SeverSocket, (sockaddr*)&addrclient, &clientlength);

         if (INVALID_SOCKET == SeverSocket)
         {
             cout << "socket failed!" << endl;
             closesocket(SeverSocket);
             WSACleanup();//释放套接字资源;
          //   return  -1;
         }
         //closesocket(SeverSocket);
         //closesocket(clientsocket);
         //WSACleanup();//释放套接字资源;
         cout << "客户端已连接!" << endl;
         while (true)
         {
         //接受客户端数据
         ZeroMemory(buf, buffsize);
         ZeroMemory(sendbuf, buffsize);
         remove = recv(clientsocket, buf, buffsize, 0);
         //参数设定：
         //int recv( SOCKET s, char *buf, int  len, int flags)
         //SOCKET s:指定接收端套接字描述符
         //char *buf:指明一个缓冲区，该缓冲区用来存放recv函数接收到的数据；
         //int  len:指明buf的长度；
         //int flags:一般置为0。
         if (SOCKET_ERROR == remove)
         {
             cout << "套接字 failed!" << endl;
             closesocket(SeverSocket);
             closesocket(clientsocket);
             WSACleanup();//释放套接字资源;
            // return  -1;
         }
         if (buf[0] == NULL)
         {
             cout << "客户端发送的数据为空" << endl;
         }
         else
         {
             cout << "客户端发送的数据：" << buf << endl;
             cout << "给客户端发送的数据：" << sendbuf << endl;
             cin >> sendbuf;
             send(clientsocket, sendbuf, sizeof(sendbuf), 0);

         }
     
     }
         
        closesocket(SeverSocket);

         closesocket(clientsocket);

         WSACleanup();
         return 0;

}

