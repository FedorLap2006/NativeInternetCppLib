#pragma once

#include <winSock2.h>
#include <windows.h>

#define T_SERVER 1
#define T_CLIENT 2

typedef long int lint;
typedef unsigned int uint;
typedef long unsigned int luint;


class Inet{
	private:
		lint IP;
		lint PORT;
		lint TYPE;
		SOCKET mainSock;
	public:
		
};

