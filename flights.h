#pragma once
#include <string>
#include "airport.h"
using namespace std;

class Airport;

class Flights {
    public:
        // constructors
        Flights();
        Flights(string airline, string airlineID, Airport source, Airport destination);

        // getters
        string getAirline(){return airline_;};
        string getAirlineID(){return airlineID_;};
        Airport getSourceAirport(){return source_;};
        Airport getDestinationAirport(){return destination_;};
        string getSourceAirportName(){return source_.getAirportName();};
        int getSourceAirportID(){return source_.getAirportID();};
        string getDestinationAirportName(){return destination_.getAirportName();};
        int getDestinationAirportID(){return destination_.getAirportID();};
        
        // calculate weights using distance formula
        // input two airport objects
        // output a double value
        double calculateWeights(Airport a, Airport b);

    private:
        string airline_;
        string airlineID_;
        Airport source_;
        Airport destination_;
        double weights_;
};