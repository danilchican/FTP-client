#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "wsock32.lib")

#include <stdio.h>
#include <windows.h>
#include <Winsock.h>
#include <iostream>

WSADATA ws;
char buf[10000];

int main()
{


	WSACleanup();

	return 0;
}