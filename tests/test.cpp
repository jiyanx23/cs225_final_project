#include "../graph.h"
#include "../cs225/catch/catch.hpp"

#include <iostream>
#include <fstream>

#include <map>
#include <vector>
#include <string>

#include "../airport.h"
#include "../flights.h"

using namespace std;

TEST_CASE("Test0"){
    REQUIRE(0 == 0);
}

TEST_CASE("Test Parsing and Getters") {
    string directory_airport = "./tests/test_airport1.dat";
    string directory_routes = "./tests/test_routes1.dat";
    Graph g(directory_airport, directory_routes);

    vector<string> airport_names = {"Goroka Airport", "Madang Airport", "Mount Hagen Kagamuga Airport", 
                                    "Nadzab Airport", "Port Moresby Jacksons International Airport", "Wewak International Airport",
                                    "Mactan Cebu International Airport", "Buka Airport", "Kimbe Airport"};

    map<int, Airport> airports = g.getAirports();
    vector<Flights> routes = g.getRoutes();

    REQUIRE(airports.size() == airport_names.size());
    int counter = 0;
    for (auto it : airports) {
        REQUIRE(it.second.getAirportName() == airport_names[counter]);
        counter++;
    }
}

TEST_CASE("Test airport object construction"){
    string airportName = "Goroka Airport";
    int airportID = 1;
    string city = "Goroka";
    string country = "Papua New Guinea";
    double lattitude = -6.081689834590001;
    double longitude = 145.391998291;
    Airport airport_test = Airport(airportName, airportID, city, country, lattitude, longitude);
    REQUIRE(airport_test.getAirportName() == airportName);
    REQUIRE(airport_test.getAirportID() == airportID);
    REQUIRE(airport_test.getCity() == city);
    REQUIRE(airport_test.getCountry() == country);
    REQUIRE(airport_test.getLattitude() == lattitude);
    REQUIRE(airport_test.getLongitude() == longitude);

}

// compaire if the two airport objects are the same
// helper function used in airport object testing
// input two airport objects
// output a boolean value
bool compareAirports(Airport ap1, Airport ap2){
    return ap1.getAirportName() == ap2.getAirportName() 
    && ap1.getAirportID() == ap2.getAirportID()
    && ap1.getCity() == ap2.getCity() 
    && ap1.getCountry() == ap2.getCountry() 
    && ap1.getLattitude() == ap2.getLattitude()
    && ap1.getLongitude() == ap2.getLongitude();
}


TEST_CASE("Test flight object construction"){
    string airline = "2B";
    string airlineID = "410";
    Airport source = Airport("Goroka Airport",1,"Goroka","Papua New Guinea", -6.081689834590001, 145.391998291);
    Airport destination = Airport("Madang Airport",2,"Madang","Papua New Guinea",-5.20707988739,145.789001465);
    Flights flight_test = Flights(airline, airlineID, source, destination);
    REQUIRE(flight_test.getAirline() == airline);
    REQUIRE(flight_test.getAirlineID() == airlineID);
    REQUIRE(compareAirports(flight_test.getSourceAirport(), source) == true);
    REQUIRE(compareAirports(flight_test.getDestinationAirport(), destination) == true);
    
}


TEST_CASE("Test Adj List"){
    // all the parsing and storing work done in main
    string directory_airport = "./tests/test_airport1.dat";
    string directory_routes = "./tests/test_routes1.dat";

    // Testing if the size of the adjacency list is equal to the number of airports given
    Graph graph_test = Graph(directory_airport, directory_routes);
    map<int, vector<int>> adj = graph_test.getAdj();
    REQUIRE(adj.size() == 9);
    REQUIRE(adj[1].size() == 3);
    REQUIRE(adj[2].size() == 2);
    REQUIRE(adj[3].size() == 4);
    REQUIRE(adj[4].size() == 3);
    REQUIRE(adj[5].size() == 4);
    REQUIRE(adj[6].size() == 1);
    REQUIRE(adj[5424].size() == 1);
    REQUIRE(adj[5419].size() == 1);
    REQUIRE(adj[4206].size() == 1);


}

TEST_CASE("Test graph object make_adj function - size 15 "){
    // all the parsing and storing work done in main
    string directory_airport = "./tests/test_airport2.dat";
    string directory_routes = "./tests/test_routes2.dat";

    // Testing if the size of the adjacency list is equal to the number of airports given
    Graph graph_test = Graph(directory_airport, directory_routes);
    map<int, vector<int>> adj = graph_test.getAdj();
    REQUIRE(adj.size() == 15);
    REQUIRE(adj[1].size() == 4);
    REQUIRE(adj[2].size() == 5);
    REQUIRE(adj[3].size() == 5);
    REQUIRE(adj[4].size() == 4);
    REQUIRE(adj[5].size() == 1);
    REQUIRE(adj[9].size() == 1);
    REQUIRE(adj[6].size() == 3);

}


TEST_CASE("Test Graph Coloring - Simple") {
    string directory_airport = "./tests/test_airport3.dat";
    string directory_routes = "./tests/test_routes3.dat";

    map<int, int> test_coloring;
    test_coloring.insert(pair<int, int>(1, 0));
    test_coloring.insert(pair<int, int>(2, 1));
    test_coloring.insert(pair<int, int>(3, 2));
    
    Graph graph_test = Graph(directory_airport, directory_routes);
    map<int, vector<int>> adj = graph_test.getAdj();
    map<int, int> coloring = graph_test.colorGraph(adj);
    for (auto i = coloring.begin(), j = test_coloring.begin(); i != coloring.end() && j != test_coloring.end(); i++, j++) {
        REQUIRE(i -> first == j -> first);
        REQUIRE(i -> second == j -> second);
    }
}


TEST_CASE("Test Graph Coloring - Complex") {
    string directory_airport = "./tests/test_airport1.dat";
    string directory_routes = "./tests/test_routes1.dat";

    map<int, int> test_coloring;
    test_coloring.insert(pair<int, int>(1, 0));
    test_coloring.insert(pair<int, int>(2, 1));
    test_coloring.insert(pair<int, int>(3, 2));
    test_coloring.insert(pair<int, int>(4, 1));
    test_coloring.insert(pair<int, int>(5, 0));
    test_coloring.insert(pair<int, int>(6, 0));
    test_coloring.insert(pair<int, int>(4206, 1));
    test_coloring.insert(pair<int, int>(5419, 1));
    test_coloring.insert(pair<int, int>(5424, 0));

    Graph graph_test = Graph(directory_airport, directory_routes);
    map<int, vector<int>> adj = graph_test.getAdj();
    map<int, int> coloring = graph_test.colorGraph(adj);
    for (auto i = coloring.begin(), j = test_coloring.begin(); i != coloring.end() && j != test_coloring.end(); i++, j++) {
        REQUIRE(i -> first == j -> first);
        REQUIRE(i -> second == j -> second);
    }
}


TEST_CASE("Test Dijkstra Simple") {
    string directory_airport = "./tests/test_airport2.dat";
    string directory_routes = "./tests/test_routes2.dat";

    Graph graph_test = Graph(directory_airport, directory_routes);

    // Test - 1 to 5
    vector<int> path15 = graph_test.Dijkstra(1, 6);

    // Test - 2 to 5
    vector<int> path25 = graph_test.Dijkstra(2, 5);

    REQUIRE(path15[0] == 1);
    REQUIRE(path15[1] == 3);
    REQUIRE(path15[path15.size()-1] == 6);
    REQUIRE(path25[0] == 2);
    REQUIRE(path25[path25.size()-1] == 5);

}
TEST_CASE("Test Dijkstra Edge (same distance)") {
    string directory_airport = "./tests/test_airport_shortest.dat";
    string directory_routes = "./tests/test_routes_shortest.dat";

    Graph graph_test = Graph(directory_airport, directory_routes);

    // Test from 1 to 6
    vector<int> path15 = graph_test.Dijkstra(1, 6);

    REQUIRE(path15[0] == 1);
    REQUIRE(path15[1] == 2);
    REQUIRE(path15[path15.size()-1] == 6);
}
TEST_CASE("Test Dijkstra Edge (not connected)") {
    string directory_airport = "./tests/test_airport_shortest1.dat";
    string directory_routes = "./tests/test_routes_shortest_empty.dat";

    Graph graph_test = Graph(directory_airport, directory_routes);

    // Test from 1 to 6
    vector<int> path15 = graph_test.Dijkstra(1, 6);

    REQUIRE(path15.size() == 0);

}
TEST_CASE("Test Calculate Weights") {
    string directory_airport = "./tests/test_airport1.dat";
    string directory_routes = "./tests/test_routes1.dat";

    Graph graph_test = Graph(directory_airport, directory_routes);
    map<int, Airport> airports = graph_test.getAirports();

    double true_distance = 106.71;

    double test_distance = airports[1].calculateWeights(airports[2]);

    REQUIRE((int)test_distance*10 == (int)true_distance*10);

}

TEST_CASE("Test Find/BFS") {
    string directory_airport = "./tests/test_airport1.dat";
    string directory_routes = "./tests/test_routes1.dat";

    Graph graph_test = Graph(directory_airport, directory_routes);
    
    REQUIRE(graph_test.Find(1) == true);
    REQUIRE(graph_test.Find(2) == true);
    REQUIRE(graph_test.Find(3) == true);
    REQUIRE(graph_test.Find(4) == true);
    REQUIRE(graph_test.Find(5) == true);
    REQUIRE(graph_test.Find(6) == true);
    REQUIRE(graph_test.Find(5424) == true);
    REQUIRE(graph_test.Find(5419) == true);
    REQUIRE(graph_test.Find(4206) == true);
}