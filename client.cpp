#include<winsock2.h>
#include <iostream>
#include<windows.h>

#include<Ws2tcpip.h>

using namespace std;
#pragma comment(lib,"WS2_32.lib")

int main()
{
    const int buffsize = 255;
    //std::cout << "Hello World!\n";
    char buf[buffsize];
    char sendbuf[buffsize];
    char Recvbuf[buffsize];
    WSADATA wsaData; //WSA变量
    WORD wsaVERSION = MAKEWORD(2, 0);
    //  SOCKET hserver;//服务器套接字



    cout << "TCP Client:" << endl;
    if (WSAStartup(wsaVERSION, &wsaData) != 0)
    {
        cout << "WSAStartup failed" << endl;
        return 1;
    }
    //创建套接字
    SOCKET sclent = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
    if (INVALID_SOCKET == sclent)
    {
        cout << "sclent failed!" << endl;
        WSACleanup();//释放套接字资源;
        return  -1;
    }
    sockaddr_in serveradd;//服务器地址
    //服务器地址
    serveradd.sin_family = AF_INET;
    //serveradd.sin_addr.S_un.S_addr =inet_pton(AF_INET,"127.0.0.1", &serveradd.sin_addr.s_addr);
    serveradd.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    serveradd.sin_port = htons(5000);
    int nServAddlen = sizeof(serveradd);
    int remove;
    while (true)
    {
        //连接服务器
        remove = connect(sclent, (sockaddr*)&serveradd, sizeof(serveradd));
        if (SOCKET_ERROR == remove)
        {
            cout << "connect failed!" << endl;
            closesocket(sclent); //关闭套接字
            WSACleanup(); //释放套接字资源
        }
        else
        {
            cout << "connect true!" << endl;

            //向服务器发送数据
            //向服务器发送数据
            ZeroMemory(buf, buffsize);
            cout << " 向服务器发送数据:  ";
            cin >> buf;
            remove = send(sclent, buf, strlen(buf), 0);
            if (SOCKET_ERROR == remove)
            {
                cout << "套接字 failed!" << endl;
                closesocket(sclent);
                WSACleanup();//释放套接字资源;
            }
            ZeroMemory(Recvbuf, buffsize);
            recv(sclent, Recvbuf, buffsize, 0); // 接收服务器端的数据， 只接收5个字符
            cout << endl << "从服务器接收数据：" << Recvbuf;
            cout << " ";

            //}
        }
    }
    //退出
    closesocket(sclent); //关闭套接字
    WSACleanup(); //释放套接字资源
    return 0;
}
