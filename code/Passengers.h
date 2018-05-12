#ifndef PASSENGERS_H
#define PASSENGERS_H

class Passen {
    int roadnet_no;
public:
    Passen(int no) {
        roadnet_no = no;
    }
    int getRoadNo() {
        return roadnet_no;
    }
};

#endif