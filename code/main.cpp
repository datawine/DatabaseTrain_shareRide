#include "Car.cpp"
#include "Passengers.h"
#include "GPTree.h"
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

const char* car_fn = "data/car.txt";
const double earth_r = 6371000.0;
const double PI = acos(-1.0);

double rad(double d) {
    return d * PI / 180;
}

double calDist(double longt1, double longt2, double lat1, double lat2) {
    double _lat1 = rad(lat1);
    double _lat2 = rad(lat2);
    double _longt1 = rad(longt1);
    double _longt2 = rad(longt2);

    double delta_lat = _lat1 - _lat2;
    double delta_long = _longt1 - _longt2;
    
    double x, y, z, dist;

    x = cos(longt1) * cos(lat1) - cos(longt2) * cos(lat2);
    y = cos(longt1) * sin(lat1) - cos(longt2) * sin(lat2);
    z = sin(lat1) - sin(lat2);

    dist = 2 * asin(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)) / 2) * earth_r;
    return dist;
}

void loadCarFile(vector<Car> &c) {
	char buf[1024];
	FILE* fp = fopen(car_fn, "r");
    string tmp_line;

	while (fgets(buf, 1024, fp) != NULL) {
        tmp_line = buf;
        tmp_line.pop_back();
        Car tmp_car(tmp_line);
        c.push_back(tmp_car);
    }
}

void bruteForce(Ans &gtree, vector<int> &res, vector<Car> &c) {

}

int main() {
    srand((unsigned)time(NULL));
    time_t t1, t2, t3, t4;

    Ans ans;
    ans.load();
    vector<Car> car_vec;

    loadCarFile(car_vec);

    vector<int> res;

    int no = rand() % 10000;
    double lat, longt;

    ans.getLL(no, lat, longt);

    double res1[1000];
    int res2[1000];

    time(&t1);

    for (int i = 0; i < 1000; i ++) {

    }

    time(&t2);

    return 0;
}