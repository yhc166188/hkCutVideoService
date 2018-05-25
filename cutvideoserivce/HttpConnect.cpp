#include "HttpConnect.h"
#include "log.h"
using namespace std;
#ifdef WIN32
#pragma comment(lib,"ws2_32.lib")
#endif
stringstream stream;
CHttpConnect::CHttpConnect()
{
#ifdef WIN32
    //此处一定要初始化一下，否则gethostbyname返回一直为空
    WSADATA wsa = { 0 };
    WSAStartup(MAKEWORD(2, 2), &wsa);
#endif
}

CHttpConnect::~CHttpConnect()
{

}
int CHttpConnect::socketInit(string host, int num)
{
    int sockfd;
    struct sockaddr_in address;
    struct hostent *server;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    if (num == 0)
        address.sin_port = htons(6666);
    if (num == 1)
        address.sin_port = htons(6667);
    if (num == 2)
        address.sin_port = htons(6668);
    if (num == 3)
        address.sin_port = htons(6669);
    server = gethostbyname(host.c_str());
    memcpy((char *)&address.sin_addr.s_addr, (char*)server->h_addr, server->h_length);
    //EV_PERSIST
    if (-1 == connect(sockfd, (struct sockaddr *)&address, sizeof(address))) {
        DBG << "connection error!" << endl;
        return -1;
    }
    //设置非阻塞
    unsigned long ul = 1;
    int iret = ioctlsocket(sockfd, FIONBIO, (unsigned long *)&ul);//设置成非阻塞模式。
    if (iret == SOCKET_ERROR)//设置失败。
    {
        Log::instance().p(YLOG_INFO, "socket:%d,设置非阻塞失败", sockfd);
    }
    Log::instance().p(YLOG_INFO, "num:%d,socket:%d,创建socket成功",num, sockfd);
    return sockfd;
}
int CHttpConnect::socketHttp(int socket,string request)
{
#ifdef WIN32
    int iret = send(socket, request.c_str(),request.size(),0);
#else
    write(sockfd,request.c_str(),request.size());
#endif
//    char buf[1024*1024] = {0};
//
//
//    int offset = 0;
//    int rc;
//
//#ifdef WIN32
//    while(rc = recv(sockfd, buf+offset, 1024,0))
//#else
//    while(rc = read(sockfd, buf+offset, 1024))
//#endif
//    {
//        offset += rc;
//    }

#ifdef WIN32
    //closesocket(sockfd);
#else
    close(sockfd);
#endif
    //buf[offset] = 0;
    //DBG << buf <<  endl;
    return iret;
}

void CHttpConnect::postData(string host,string path,string post_content,int num)
{
    //POST请求方式
	stream.str("");
    stream << "POST " << path;
    stream << " HTTP/1.0\r\n";
    stream << "Host: "<< host << "\r\n";
    stream << "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n";
    stream << "Content-Type:application/x-www-form-urlencoded\r\n";
    stream << "Content-Length:" << post_content.length()<<"\r\n";
    stream << "Connection:close\r\n\r\n";
    stream << post_content.c_str();

    //socketHttp(host, stream.str(),num);
}

int CHttpConnect::getData(int socket,string path,string get_content)
{
    //GET请求方式
    string str;
	stream.str("");
    stream << "GET " << path << "?" << get_content;
    stream << " HTTP/1.0\r\n";
    stream << "Host: " << "127.0.0.1" << "\r\n";
    stream <<"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n";
    stream <<"Connection:close\r\n\r\n";
	str=stream.str();
    int iret = send(socket, str.c_str(), str.size(), 0);
    return iret;
}