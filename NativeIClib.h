#pragma once


#include <winSock2.h>
#include <windows.h>
#include <string>

using namespace std;

#define T_SERVER 1
#define T_CLIENT 2

#define DEF_NOUSED_PORT 585

typedef long int lint;
typedef unsigned int uint;
typedef long unsigned int luint;
typedef char* lpstrI;
typedef SOCKET HSOCK;

bool StartupLib();

class Inet{
	protected:
		lpstrI IP;
		lint PORT;
		HSOCK mainSock;
		int protocol;
		bool bootcheck;
	public:
		bool SendM(size_t countinfo,lpstrI info);
		lpstrI RecvM(size_t countinfo,bool &CRecv);
};

class Server : public Inet{
	private:
		HSOCK recvsock;
		SOCKADDR_IN serverAddr;
	public:
		bool errorinit=false;
		Server(lpstrI IP,lint PORT=DEF_NOUSED_PORT,lint TypeSock);
		bool ConnectS();
		void DisConnectS();
};

class Client : public Inet{
	private:
		SOCKADDR_IN serverSockAddr;
	public:
		Client(lpstrI IP,lint PORT=DEF_NOUSED_PORT,lint TypeSock);
		bool ConnectC();
		void DisConnectC();
};


