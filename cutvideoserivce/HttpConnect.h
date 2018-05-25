#pragma once
 
#include <string>
#include <sstream>
using namespace std;

class CHttpConnect
{
public:
	CHttpConnect();
	~CHttpConnect();
	int socketHttp(int socket,string request);
	void postData(string host,string path,string post_content,int num);
	int getData(int socket,string path,string post_content);
    int socketInit(string host, int num);
private:
	stringstream DBG;
};