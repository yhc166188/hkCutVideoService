#pragma once
 
#include <string>
#include <sstream>
using namespace std;
typedef struct socket_s
{
    int port;
    int socked;
}sockets_s;

class CHttpConnect
{
public:
	CHttpConnect();
	~CHttpConnect();
	int socketHttp(int socket,string request);
	void postData(string host,string path,string post_content,int num);
	int getData(int socket,string path,string post_content);
    int socketInit(string host,int num, sockets_s &socket);
private:
	stringstream DBG;
};