#include "Calculation.h"
#include <fstream>
#include <iostream>

const double earth_r = 6371000.0;
const double PI = acos(-1.0);

int road_dist[4][4], start_dist[2][4];

double rad(double d) {
    return d * PI / 180;
}

double calEucDist(double longt1, double longt2, double lat1, double lat2) {
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

void swap(int &a,int &b){
    int temp = a;
    a = b;
    b = temp;
}

void calRoadDist(int start_index, int *list, int low, int high, int &m_d, int *seq){
    if(low == high){
        int sum = 0;
        sum += start_dist[start_index][list[0]];
        for(int i = 0;i < low; i ++) {
            sum += road_dist[list[i]][list[i + 1]];
        }
        if (m_d > sum) {
            m_d = sum;
            for (int i = 0; i <= low; i ++) {
                seq[i] = list[i];
            }
        }
    }else{
        for(int i = low;i <= high; i ++){
            swap(list[i], list[low]); 
            calRoadDist(start_index, list, low + 1, high, m_d, seq);
            swap(list[i], list[low]);
        }
    }
}

void genRes(Ans &ans, vector<Car> &car_vec, vector<int> &rn_list, int start_no, int dest_no) {
    ofstream out;
    out.open("ans.json", ios::trunc);

    vector<int> c;
    c = ans.getRange(start_no, 10000, rn_list);

    double car_longt, car_lat, tmp_longt, tmp_lat;
    int car_posi, passen_posi[4];
    int passen_num;
    int d1, d2, d3, d4;
    int list[4], new_way[4], old_way[4];

    bool hasbefore = false;
    out << "[" << endl;

    int cnt = 0;

    for (int i = 0; i < c.size(); i ++) {
        passen_num = car_vec[c[i]].passenger_num;
        if (passen_num < 4) {
            car_posi = car_vec[c[i]].roadnet_posi;
            for (int j = 0; j < passen_num; j ++) {
                passen_posi[j] = car_vec[c[i]].dest_rn[j];
            }
            passen_posi[passen_num] = dest_no;

            for (int j = 0; j <= passen_num; j ++) {
                start_dist[0][j] = ans.get_min_distance(car_posi, passen_posi[j]);
                start_dist[1][j] = ans.get_min_distance(start_no, passen_posi[j]);
            }
            for (int j = 0; j <= passen_num; j ++) {
                for (int k = j + 1; k <= passen_num; k ++) {
                    road_dist[j][k] = ans.get_min_distance(passen_posi[j], passen_posi[k]);
                    road_dist[k][j] = road_dist[j][k];
                }
            }

            d1 = 10000000;
            d3 = 10000000;
            for (int j = 0; j <= passen_num; j ++) {
                list[j] = j;
                old_way[j] = j;
            } 
            calRoadDist(0, list, 0, passen_num - 1, d1, old_way);
            d2 = ans.get_min_distance(car_posi, start_no);
            for (int j = 0; j <= passen_num; j ++) {
                list[j] = j;
                new_way[j] = j;
            } 
            calRoadDist(1, list, 0, passen_num, d3, new_way);;
            d4 = start_dist[1][passen_num];

            if ((d2 + d3 - d1 <= 10000) and (d3 - d4 <= 10000)) {
                cnt ++;
                if (cnt == 11)
                    break;
                if (!hasbefore)
                    out << "{" << endl;
                else
                    out << ",{" << endl;
                hasbefore = true;

                out << "\"route\": [{" << endl;
                ans.getLL(car_posi, car_longt, car_lat);
                out << "\"lngt\": " << car_longt << "," << endl;
                out << "\"lat\": " << car_lat << "}";

                ans.getLL(start_no, tmp_longt, tmp_lat);
                out << ",{" << endl;
                out << "\"lngt\": " << tmp_longt << "," << endl;
                out << "\"lat\": " << tmp_lat << "}";

                for (int j = 0; j <= passen_num; j ++) {
                    ans.getLL(passen_posi[new_way[j]], tmp_longt, tmp_lat);
                    out << ",{" << endl;
                    out << "\"lngt\": " << tmp_longt << "," << endl;
                    out << "\"lat\": " << tmp_lat << "}";
                }

                out << "]" << endl;
                out << "}";

                cout << "---------" << endl;
                cout << car_posi << "->" << start_no << endl;
                cout << start_no << "->" << passen_posi[new_way[0]] << endl;
                for (int j = 1; j <= passen_num; j ++) {
                    cout << passen_posi[new_way[j - 1]] << "->" << passen_posi[new_way[j]] << endl;
                }
            }
        }
    }

    out << "]" << endl;
    out.close();
}