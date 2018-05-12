#ifndef CAR_H
#define CAR_H

#include <string>

using namespace std;

class Car {

public:
    Car(string s);

    int no;
    int passenger_num;

    int roadnet_posi;
    double longitude, latitude;

    int dest_rn[4];
    double dest_long_la[4][2];   
};

#endif