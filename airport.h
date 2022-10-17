#pragma once

#include <string>
#include <vector>
#include <cmath>

using namespace std;
class Airport {
    public:
        // Default Constructor
        Airport();
        /*
        * Constructor
        * inputs: string airportName, int airportID, string city, string country, double lattitude, double longitude
        */
        Airport(string airportName, int airportID, string city, string country, double lattitude, double longitude);

        // Getters
        int getAirportID();
        string getAirportName();
        string getCity();
        string getCountry();
        double getLattitude();
        double getLongitude();

        /*
        * Calculates the Distance/Weight from 2 Airports (Assuming it's a straight line)
        * Example use AirportA.calculateWeight(AirportB)
        * Input: this, Airport b
        * Output: double, weight/distance from 2 Airports (Assuming it's a straight line)
        */
        double calculateWeights(Airport b); // same as the function in Flights class
    private:
        int airportID_;
        string airportName_;
        string city_;
        string country_;
        double lattitude_;
        double longitude_;
};