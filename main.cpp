#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <map>
#include "airport.h"
#include "flights.h"
#include "graph.h"

using namespace std;

int main() {

        // ------------ sample usage of parser ------------ //
    string directory_airport = "./Resources/airport.dat";
    string directory_routes = "./Resources/routes.dat";
    // string directory_airport = "./tests/test_airport1.dat";
    // string directory_routes = "./tests/test_routes1.dat";

    // testing output of a graph
    Graph g = Graph(directory_airport, directory_routes);

    map<int, Airport> airports = g.getAirports();

    int airport1;
    int airport2;
    
    bool error = false;
    while (error == false) {
        cout << "Please enter your source airport ID: ";
        cin >> airport1;
        map<int, Airport>::iterator lookup_airport1 = airports.find(airport1);
        if (lookup_airport1 == airports.end()) {
            cout << "Please enter a valid source airport." << endl;
        } else {
            cout << "You entered: " << lookup_airport1 -> second.getAirportName() << endl;
            error = true;
        }
    }
    
    error = false;
     while (error == false) {
        cout << "Please enter your destination airport ID: ";
        cin >> airport2;
        map<int, Airport>::iterator lookup_airport2 = airports.find(airport2);
        if (lookup_airport2 == airports.end()) {
            cout << "Please enter a valid destination airport." << endl;
        } else {
            cout << "You entered: " << lookup_airport2 -> second.getAirportName() << endl;
            error = true;
        }
    }
    
    vector<int> path = g.Dijkstra(airport1, airport2);

    if (path.empty()) {
        cout << "There's No Path Between " << airports.find(airport1)->second.getAirportName() << " and " << airports.find(airport2)->second.getAirportName() << "." << endl;
        return 0;
    }

    for (size_t i = 0; i < path.size(); i++) {
        map<int, Airport>::iterator lookup_airport = airports.find(path[i]);
        if (i == path.size() - 1) {
            cout << lookup_airport -> second.getAirportName();
            break;
        }
        if (lookup_airport != airports.end()) {
            cout << lookup_airport -> second.getAirportName() << " -> ";
        }    
    }
    cout << endl;
    return 0;
}
