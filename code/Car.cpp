#include "Car.h"
#include <iostream>

using namespace std;

//0 2 116.65644,39.89045,285434 116.68906,39.91686,121573 116.67723,40.11989,227465
Car::Car(string s) {
    int h = 0, index = 0, comma1, comma2;
    string tmp;
    for (int i = 0; i <= s.length(); i ++) {
        if (s[i] == ' ' or i == s.length()) {
            tmp = s.substr(h, i - h);
            h = i + 1;

            switch(index) {
                case 0:
                    no = atoi(tmp.c_str());
                    index ++;
                    break;
                case 1:
                    passenger_num = atoi(tmp.c_str());
                    index ++;
                    break;
                case 2:
                    comma1 = -1;
                    comma2 = -1;
                    for (int j = 0; j < tmp.length(); j ++) {
                        if (tmp[j] == ',') {
                            if (comma1 == -1) {
                                comma1 = j;
                            } else {
                                comma2 = j;
                            }
                        }
                    }

                    longitude = atof(tmp.substr(0, comma1).c_str());
                    latitude = atof(tmp.substr(comma1 + 1, comma2 - comma1 -1).c_str());
                    roadnet_posi = atoi(tmp.substr(comma2 + 1, tmp.length() - comma2 - 1).c_str());
                    index ++;
                    break;
                default:
                    comma1 = -1;
                    comma2 = -1;
                    for (int j = 0; j < tmp.length(); j ++) {
                        if (tmp[j] == ',') {
                            if (comma1 == -1) {
                                comma1 = j;
                            } else {
                                comma2 = j;
                            }
                        }
                    }

                    dest_long_la[index - 3][0] = atof(tmp.substr(0, comma1).c_str());
                    dest_long_la[index - 3][1] = atof(tmp.substr(comma1 + 1, comma2 - comma1 -1).c_str());
                    dest_rn[index - 3] = atoi(tmp.substr(comma2 + 1, tmp.length() - comma2 - 1).c_str());
                    index ++;
            }
        }
    }
}