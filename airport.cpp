#include "airport.h"
#include <iostream>
using namespace std;

// Default Constructor
Airport::Airport() {}

/*
* Constructor
* inputs: string airportName, int airportID, string city, string country, double lattitude, double longitude
*/
Airport::Airport(string airportName, int airportID, string city, string country, double lattitude, double longitude) {
    airportName_ = airportName;
    airportID_ = airportID;
    city_ = city;
    country_ = country;
    lattitude_ = lattitude;
    longitude_ = longitude;
}

// Getters
int Airport::getAirportID() {
    return airportID_;
}

string Airport::getAirportName() {
    return airportName_;
}

string Airport::getCity() {
    return city_;
}

string Airport::getCountry() {
    return country_;
}

double Airport::getLattitude() {
    return lattitude_;
}

double Airport::getLongitude() {
    return longitude_;
}

/*
* Calculates the Distance/Weight from 2 Airports (Assuming it's a straight line)
* Example use AirportA.calculateWeight(AirportB)
* Input: this, Airport b
* Output: double, weight/distance from 2 Airports (Assuming it's a straight line)
*/
double Airport::calculateWeights(Airport b){
    int r = 6371;
    double t1 = this->getLattitude() * M_PI / 180;
    double t2 = b.getLattitude() * M_PI / 180;
    double dt = (b.getLattitude() - this->getLattitude()) * M_PI / 180;
    double dl = (b.getLongitude() - this->getLongitude()) * M_PI / 180;
    double a = sin(dt/2) * sin(dt/2) + \
               cos(t1) * cos(t2) * \
               sin(dl/2) * sin(dl/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = r * c;
    return d;
}