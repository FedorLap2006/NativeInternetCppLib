#include "NativeIClib.h"


bool StartupLib(){
	WSADATA wsadata;

	WORD libver=MAKEWORD(2,1);
	
	if(WSAStartup(libver,&wsadata) != 0)
	{
		return false;
	}
	return true;
}


// Inet Class

bool Inet::SendM(SOCKET lsock,size_t countinfo,lpstrI info){
	HSOCK asock;
	size_t cbyte=send(lsock,lpstrI,countinfo,0);
	if(countinfo <=0) return NULL;
	if(cbyte < countinfo) return false;
	return true;
}

lpstrI Inet::RecvM(SOCKET lsock,size_t countinfo,bool &CRecv){
	lpstrI buff;
	if(countinfo <=0) return NULL;
	size_t cread=recv(lsock,buff,countinfo,0);
	if(cread < countinfo) {CRecv=false;return NULL;}
	else CRecv=true;
	return buff;
}

// Server


Server::Server(lint IP,lint PORT,lint TypeSock){
	this->serverAddr.sin_family=AF_INET;
	this->serverAddr.sa_data=htonl(IP);
	this->serverAddr.sin_port=PORT;
	
	this->mainSock=socket(AF_INET,TypeSock,protocol);
	bootcheck=false;
}

bool Server::ConnectS(){
	if(bootcheck) return true;
	if(bind(mainSock,(SOCKADDR*)&serverAddr,sizeof(serverAddr))!=0){
		errorinit=true;
		return false;
	}
	recvsock=accept(mainSock,&serverAddr,sizeof(serverAddr));
	bootcheck=true;
	return true;
}

void Server::DisConnectS(){
	closesocket(recvsock);
	if(!bootcheck) return;
	closesocket(mainSock);
}

Client::Client(lint IP,lint PORT,lint TypeSock){
	this->serverSockAddr.sin_family=AF_INET;
	this->serverSockAddr.sa_data=htonl(IP);
	this->serverSockAddr.sin_port=PORT;
	
	this->mainSock=socket(AF_INET,TypeSock,protocol);
	bootcheck=false;
}

bool Client::ConnectC(){
	if(bootcheck) return true;
	if(connect(mainSock,(SOCKADDR*)&serverSockAddr,sizeof(serverAddr))!=0){
		errorinit=true;
		return false;
	}
	bootcheck=true;
	return true;
}

void Server::DisConnectS(){
	if(!bootcheck) return;
	closesocket(mainSock);
}


