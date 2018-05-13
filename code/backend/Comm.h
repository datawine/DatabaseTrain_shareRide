#ifndef COMM_H
#define COMM_H

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>

#define SRVPORT 10005
#define CONNECT_NUM 5
#define MAX_NUM 80

int initSocket();

#endif