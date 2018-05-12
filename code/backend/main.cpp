#include "Car.h"
#include "GPTree.h"
#include "Calculation.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include<unistd.h>

#define SRVPORT 10005
#define CONNECT_NUM 5
#define MAX_NUM 80

using namespace std;

const char* car_fn = "data/car.txt";

void loadCarFile(vector<Car> &c, vector<int> &rn_list) {
	char buf[1024];
	FILE* fp = fopen(car_fn, "r");
    string tmp_line;

    int line_cnt = 0;
	while (fgets(buf, 1024, fp) != NULL) {
        line_cnt ++;
        tmp_line = buf;
        tmp_line.pop_back();
        Car tmp_car(tmp_line);
        c.push_back(tmp_car);
        rn_list.push_back(tmp_car.roadnet_posi);
    }
}

int main() {
    clock_t t1, t2;

    Ans ans;
    ans.init();
    ans.load();
    
    vector<Car> car_vec;

    vector<int> c;
    vector<int> rn_list;
    loadCarFile(car_vec, rn_list);

    int start_no = 2345, dest_no = 2346;

    int serverSock = -1, clientSock = -1;
    struct sockaddr_in serverAddr;

    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSock < 0) {
        printf("socket creation failed\n");
        exit(-1);
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

    char revBuf[MAX_NUM]={0};
    char sedBuf[MAX_NUM]={0};
    int i = 0;
    while(1)
    {
        clientSock = accept(serverSock, NULL, NULL);
        while(1) {
            if(read(clientSock,revBuf,MAX_NUM) != -1) {
                printf("Client:%s\n", revBuf);
            } else {
                break;
            }
            t1 = clock();

            genRes(ans, car_vec, rn_list, start_no, dest_no);

            t2 = clock();

            cout << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
            strcpy(sedBuf,"Hello Client.");
            if(write(clientSock, sedBuf, sizeof(sedBuf)) == -1) {
                printf("Send error!\n");
            }
            bzero(revBuf,sizeof(revBuf));
            bzero(sedBuf,sizeof(sedBuf));
        }
        close(clientSock);
    }
    close(serverSock);


    return 0;
}