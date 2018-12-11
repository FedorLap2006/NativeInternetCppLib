#pragma once


#include <winSock2.h>
#include <windows.h>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

#define T_SERVER 1
#define T_CLIENT 2

#define DEF_NOUSED_PORT 585




typedef long int lint;
typedef unsigned int uint;
typedef long unsigned int luint;
typedef char* lpstr;
typedef const char* cplstr;
typedef SOCKET HSOCK;


class Inet{
	protected:
		lpstrI IP;
		lint PORT;
		HSOCK mainSock;
		int protocol;
		bool isAvaible=true;
	public:
		virtual void Send(string &sender);
		virtual void Recv(string &reader);
		bool getAvaible(){return isAvaible;}
};

class Client : public Inet{
	private:
		struct sockaddr_in saddr;
	public:
		Client(string ip,int port);
		~Client(){WSACleanup();if(isAvaible){closeSocket(mainSock);isAvaible=false;}}
		
		void Close(){if(isAvaible){closeSocket(mainSock); isAvaible=false;}}
		void Connect(){if(isAvaible){if(connect(mainSock,saddr,sizeof(saddr)) < 0) isAvaible=false;}}
};

class Server : public Inet{
	private:
		struct sockaddr_in sbindaddr;
		bool isThreads=false;
		bool readInitcheck=false;
	public:
		void ReadInit();
		Server(string ip,int port,bool threads);
		~Server(){WSACleanup();if(isAvaible){closeSocket(mainSock);isAvaible=false;}}
		void Send(string &sender) override;
		void Recv(string &reader) override;

		void Close(){if(isAvaible){closeSocket(mainSock); isAvaible=false;}}
		void Connect(){if(isAvaible){if(connect(mainSock,saddr,sizeof(saddr)) < 0) isAvaible=false;}}
};


