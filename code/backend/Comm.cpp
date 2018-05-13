#include "Comm.h"

int initSocket() {
    int serverSock = -1, clientSock = -1;
    struct sockaddr_in serverAddr;

    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSock < 0) {
        printf("socket creation failed\n");
        return -1;
    }
    printf("socket create successfully.\n");

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons((u_short) SRVPORT);
    serverAddr.sin_addr.s_addr = htons(INADDR_ANY);
    bind(serverSock,(struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in));
    printf("Bind successful.\n");

    if(listen(serverSock,10)==-1) {
        printf("Listen error!\n");
    }
    printf("Start to listen!\n");
    
    return serverSock;
}
