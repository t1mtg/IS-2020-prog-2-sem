#pragma once
#include <vector>
#include <string>
using namespace std;
class ST {
public:
    string number;
    string type_of_vehicle;
    vector<string> location;
    vector <string> routes;
    vector <double> coords;
};

double dist(double x1, double y1, double x2, double y2);
string maximum_rout(int type, vector<ST> &all_stations, vector<string> &vehicle_types, int number_of_stations);
double maximum_length_route(int type, vector<ST> &all_stations, vector<string> &vehicle_types, int number_of_stations);
string street(vector<ST> &all_stations, int number_of_stations);
