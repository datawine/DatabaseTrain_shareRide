#ifndef CAR_H
#define CAR_H

#include <string>

using namespace std;

class Car {
    int no;
    int passenger_num;

    int roadnet_posi;
    double longitude, latitude;

    int dest_rn[4];
    double dest_long_la[4][2];   

public:
    Car(string s);

    void CarLL(double &a, double &b) { a = longitude; b = latitude; }
    int CarNo() { return no; }
};

#endif