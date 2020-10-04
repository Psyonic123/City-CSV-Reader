#pragma once
#pragma warning(disable : 4996)

#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <fstream>

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#ifndef M_PI
#define M_PI    3.1415926535897932384626433832795
#endif
using namespace std;
static const double earth_radius_km = 6371.0;

class City
{
public:
	City();
	~City();

	double deg_rad(double deg);
	double haversine_distance(double latitude1, double longitude1, double latitude2,
		double longitude2);
	void fillVector(vector <City>& Index);
	void printVector(vector<City>& Index);
	void loop(vector<City>& Index);
	void calcDistances(string choiceLat, string choiceLon, vector<City>& Index);

	string getName();
	string getCountry();
	string getLat();
	string getLon();
	string getID();
	double getDistance();

	void setName(string name);
	void setCountry(string country);
	void setLat(string lat);
	void setLon(string lon);
	void setID(string ID);
	void setDistance(double distance);
private:

	string ID;
	string name;
	string country;
	string lat;
	string lon;
	double distance;

};

 