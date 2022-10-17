#include "flights.h"
#include <cmath>
using namespace std;


// construcor
Flights::Flights(string airline, string airlineID, Airport source, Airport destination) :
airline_(airline), airlineID_(airlineID), source_(source), destination_(destination){
    weights_ = calculateWeights(source, destination);
}

    // calculate weights using distance formula
    // input two airport objects
    // output a double value
double Flights::calculateWeights(Airport a, Airport b){
    int earth_radius = 6371;
    double dlat = (b.getLattitude() - a.getLattitude()) * (M_PI / 180);
    double dlon = (b.getLongitude() - a.getLongitude()) * (M_PI / 180);
    double value_a = sin(dlat / 2) * sin(dlat / 2) + cos(a.getLattitude()* (M_PI / 180)) * cos(b.getLattitude()* (M_PI / 180)) * sin(dlon/2) * sin(dlon/2);
    double value_b = 2 * atan2(sqrt(value_a), sqrt(1-value_a));
    double value_d = earth_radius * value_b;
    return value_d;
}