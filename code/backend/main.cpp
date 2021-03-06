#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "Car.h"
#include "GPTree.h"
#include "Calculation.h"
#include "Comm.h"

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

    vector<int> c, rn_list;
    loadCarFile(car_vec, rn_list);

    int start_no = 2345, dest_no = 2346;

    int serverSock = -1, clientSock = -1;

    double tmp_lngt1, tmp_lat1, tmp_lngt2, tmp_lat2;
    double start_lngt, start_lat, dest_lngt, dest_lat; 


    serverSock = initSocket();
    char revBuf[MAX_NUM]={0};
    char sedBuf[MAX_NUM]={0};
    string revMsg;
    while(1)
    {
        clientSock = accept(serverSock, NULL, NULL);
        while(1) {
            if(read(clientSock,revBuf,MAX_NUM) != -1) {
                revMsg = revBuf;
            } else {
                break;
            }
            t1 = clock();

            cout << revMsg << endl;

            parseData(revMsg, tmp_lngt1, tmp_lat1, tmp_lngt2, tmp_lat2);

            cout << tmp_lngt1 << endl;
            cout << tmp_lat1 << endl;
            cout << tmp_lngt2 << endl;
            cout << tmp_lat2 << endl;

            start_no = ans.getClose(tmp_lngt1, tmp_lat1, start_lngt, start_lat);
            dest_no = ans.getClose(tmp_lngt2, tmp_lat2, dest_lngt, dest_lat);

            cout << "road_net_no:" << endl;
            cout << start_no << " " << dest_no << endl;
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