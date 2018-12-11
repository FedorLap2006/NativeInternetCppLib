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
		isAvaible=true;

		sbindaddr.sin_family=AF_INET;
		sbindaddr.sin_port=port;
		sbindaddr.sin_addr=inet_addr(ip.c_str());
	}

	if(bind(mainSock,sbindaddr,sizeof(sbindaddr)) < 0) isAvaible=false;
	if(threads) { /* do work */}
}

