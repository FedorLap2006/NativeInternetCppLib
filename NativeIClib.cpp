#include "NativeIClib.h"

Client::Client(string ip,int port){
	WSADATA wsadata;

	WORD libver=MAKEWORD(2,1);
	
	if(WSAStartup(libver,&wsadata) != 0)
	{
		isAvaible=false;
	}
	else {
		isAvaible=true;

		saddr.sin_family=AF_INET;
		saddr.sin_port=port;
		saddr.sin_addr=inet_addr(ip.c_str());
	}

}

Server::Server(string ip,int port,bool threads){
	WSADATA wsadata;

	WORD libver=MAKEWORD(2,1);
	
	if(WSAStartup(libver,&wsadata) != 0)
	{
		isAvaible=false;
	}
	else {
		mainSock=socket(AF_INET, SOCK_STREAM, 0);
		isAvaible=true;

		sbindaddr.sin_family=AF_INET;
		sbindaddr.sin_port=port;
		sbindaddr.sin_addr=inet_addr(ip.c_str());

	}

	if(bind(mainSock,sbindaddr,sizeof(sbindaddr)) < 0) isAvaible=false;
	if(threads) { /* do work */}
}

int Inet::Send(string &sender){
	if(!isAvaible) return -1;
	return send(mainSock,sender.c_str(),sender.size(),0);
}
int Inet::Recv(string &reader,size_t size){
	if(!isAvaible) return -1;
	char *buffer = new char[size];
	int b = recv(mainSock,buffer,size,0);
	reader=buffer;
	delete[] buffer;
	return b;
}

int Recv(string &reader,size_t size){
	if(!readInitcheck) ReadInit();
	if(!isAvaible) return -1;
	char *buffer = new char[size];
	int b = recv(haccept,buffer,size,0);
	reader=buffer;
	delete[] buffer;

	closeSocket(haccept);
	readInitcheck=false;
	return b;
}

