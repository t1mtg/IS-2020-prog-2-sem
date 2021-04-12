#include "stations.h"
#include <cmath>
#include <algorithm>
double dist(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
string maximum_rout(int type, vector<ST> &all_stations, vector<string> &vehicle_types, int number_of_stations) {
    vector<string> routes;
    vector<int> routes_length;
    for (int i = 0; i < number_of_stations; i++) {
        for (int j = 0; j < all_stations[i].routes.size(); j++) {
            if ((std::find(routes.begin(), routes.end(), all_stations[i].routes[j]) == routes.end()) &&
                all_stations[i].type_of_vehicle == vehicle_types[type])
                routes.push_back(all_stations[i].routes[j]);
        }
    }
    routes_length.reserve(routes.size());
    for (int i = 0; i < routes.size(); i++)
        routes_length.push_back(0);

    for (int i = 0; i < routes.size(); i++) {
        for (int j = 0; j < number_of_stations; j++) {
            if (std::find(all_stations[j].routes.begin(), all_stations[j].routes.end(), routes[i]) != all_stations[j].routes.end() && all_stations[j].type_of_vehicle == vehicle_types[type])
                routes_length[i] += 1;
        }
    }
    std::vector<int>::iterator result;
    result = max_element(routes_length.begin(), routes_length.end());
    return routes[std::distance(routes_length.begin(), result)];
}

double maximum_length_route(int type, vector<ST> &all_stations, vector<string> &vehicle_types, int number_of_stations) {
    vector<string> routes;
    vector<vector<double>> stations;
    vector<double> routes_length;
    for (int i = 0; i < number_of_stations; i++) {
        for (int j = 0; j < all_stations[i].routes.size(); j++) {
            if ((std::find(routes.begin(), routes.end(), all_stations[i].routes[j]) == routes.end()) &&
                all_stations[i].type_of_vehicle == vehicle_types[type])
                routes.push_back(all_stations[i].routes[j]);
        }
    }
    for (int i = 0; i < number_of_stations; i++) {
        for (int j = 0; j < routes.size(); j++) {
            stations.emplace_back();
            if ((std::find(all_stations[i].routes.begin(), all_stations[i].routes.end(), routes[j]) != all_stations[i].routes.end()) &&
                all_stations[i].type_of_vehicle == vehicle_types[type]) {
                stations[j].push_back(i);
            }
        }
    }

    for (int i = 0; i < routes.size(); i++) {
        double length = 0;
        for (int j = 0; j < stations[i].size() - 1; j++) {
            double x1 = all_stations[stations[i][j]].coords[0];
            double y1 = all_stations[stations[i][j]].coords[1];
            double x2 = all_stations[stations[i][j+1]].coords[0];
            double y2 = all_stations[stations[i][j+1]].coords[1];
            length += dist(x1, y1, x2, y2);
        }
        routes_length.push_back(length);
    }

    std::vector<double>::iterator result;
    result = max_element(routes_length.begin(), routes_length.end());
    return stod(routes[std::distance(routes_length.begin(), result)]);
}

string street(vector<ST> &all_stations, int number_of_stations) {
    vector<string> streets;
    vector<int> street_length;
    for (int i = 0; i < number_of_stations; i++) {
        for (auto & j : all_stations[i].location) {
            if ((std::find(streets.begin(), streets.end(), j) == streets.end()))
                streets.push_back(j);
        }
    }
    street_length.reserve(streets.size());
    for (int i = 0; i < streets.size(); i++)
        street_length.push_back(0);

    for (int i = 0; i < streets.size(); i++) {
        for (int j = 0; j < number_of_stations; j++) {
            if (std::find(all_stations[j].location.begin(), all_stations[j].location.end(), streets[i]) != all_stations[j].location.end())
                street_length[i] += 1;
        }
    }
    /*for (int i = 0; i < streets.size(); i++)
        cout << streets[i] << " " << street_length[i] << endl;*/
    std::vector<int>::iterator result;
    result = max_element(street_length.begin(), street_length.end());
    return streets[std::distance(street_length.begin(), result)];
}
