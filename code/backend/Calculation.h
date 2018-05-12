#ifndef CALCULATION_H
#define CALCULATION_H

#include "GPTree.h"
#include "Car.h"
#include <vector>
#include <cmath>

double calEucDist(double longt1, double longt2, double lat1, double lat2);
void calRoadDist(int start_index, int *list, int low, int high, int &m_d, int *seq);

void genRes(Ans &ans, vector<Car> &car_vec, vector<int> &rn_list, int start_no, int dest_no);

#endif