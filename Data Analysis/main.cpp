#include <iostream>
#include <vector>
#include "pugixml.hpp"
#include "pugixml.cpp"
#include <sstream>
#include <algorithm>
#include "stations.h"
using namespace std;


int main(){
    system("chcp 65001");
    int number_of_stations = 0;
    vector<string> vehicle_types;
    vector<ST> all_stations;
    pugi::xml_document doc;
    if (!doc.load_file("data_orig.xml")) return -1;
    pugi::xml_node stations = doc.child("dataset");

    for (pugi::xml_node station = stations.first_child(); station; station = station.next_sibling())
    {
        ST cur_station;
        cur_station.number = station.child_value("number");
        number_of_stations = stoi(cur_station.number);
        cur_station.type_of_vehicle = station.child_value("type_of_vehicle");
        if (std::find(vehicle_types.begin(), vehicle_types.end(), cur_station.type_of_vehicle) == vehicle_types.end())
            vehicle_types.push_back(cur_station.type_of_vehicle);
        string tmp_str;
        tmp_str = station.child_value("location");
        for (int i = 0; i < tmp_str.size(); i++)
            if (tmp_str[i] == ',')
                tmp_str.erase(i+1);
        if (!tmp_str.empty()) {
            std::stringstream ss(tmp_str);
            std::vector<std::string> tokens;
            std::string buf;
            while (std::getline(ss, buf, ','))
                cur_station.location.push_back(buf);
        }

        tmp_str = station.child_value("routes");
        for (char & t : tmp_str) {
            if (t == '.' || t == ',')
                t = ' ';
        }
        //cout << tmp_str << endl;
        std::stringstream ss(tmp_str);
        std::string buf;
        while (ss >> buf)
            cur_station.routes.push_back(buf);

        int i = 0;
        string crd1;
        string crd2;
        tmp_str = station.child_value("coordinates");
        while (tmp_str[i] != ',') {
            crd1 += tmp_str[i];
            i++;
        }
        crd2 = tmp_str.substr(i+1);
        cur_station.coords.push_back(stod(crd1));
        cur_station.coords.push_back(stod(crd2));

        all_stations.push_back(cur_station);
    }

    cout << "Маршрут автобуса с наибольшим числом остановок - " << maximum_rout(0, all_stations, vehicle_types, number_of_stations) << endl;
    cout << "Маршрут троллейбуса с наибольшим числом остановок - " << maximum_rout(1, all_stations, vehicle_types, number_of_stations) << endl;
    cout << "Маршрут трамвая с наибольшим числом остановок - " << maximum_rout(2, all_stations, vehicle_types, number_of_stations) << endl;
    cout << "Маршрут автобуса с наибольшей длиной - " << maximum_length_route(0, all_stations, vehicle_types, number_of_stations) << endl;
    cout << "Маршрут троллейбуса с наибольшей длиной - " << maximum_length_route(1, all_stations, vehicle_types, number_of_stations) << endl;
    cout << "Маршрут трамвая с наибольшей длиной - " << maximum_length_route(2, all_stations, vehicle_types, number_of_stations) << endl;
    cout << "Улица с наибольшим количеством остановок - " << street(all_stations,  number_of_stations);
    return 0;
}