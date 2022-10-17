#pragma once
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "airport.h"
#include "flights.h"
#include <queue>
#include <stack>

// #define INFINITY 99999999.99

using namespace std;

class Graph {
    public:
        // Constructor
        Graph(string airport_directory, string routes_directory);

        /* 
        * file_parser: Parse the data from a .dat file.
        * Function Inputs: The directory of a .dat file containing all information seperated by "," and newlines
        * Function Outputs: A vector of vector - vector<vector<string>>
        *                  where each vector represents all information needed 
        *                  to construct an object (such as airports, flights, etc.).
        */
        vector<vector<string>> file_parser(string directory);

        // Creates and Adjecency List from data in airports_ and routes_
        void make_adj();

        // Turns String Data into Airport Objects
        void parse_airport(string dir);

        // Turns String Data into Flight Objects
        void parse_routes(string dir);
    
        // Getters
        map<int, vector<int>> getAdj();
        map<int, Airport> getAirports();
        vector<Flights> getRoutes();

        /* 
        * Find: A private method implemented for BFS.
        * Function Inputs: The airportID of the airport we are trying to find. 
        * Function Outputs: Return true if found, return false if not found.
        * Function Efficiency: The algorithm will have a runtime of O(n), 
        *                    since the worst case will be visiting every node in the graph.
        */
        bool Find(int id);

        /* 
        * BFS: Traverse the whole graph and find whether there exists an airport with the same ID as source airport.
        * Function Inputs: Two airport IDs we are trying to find the shortest path between. 
        * Function Outputs: The output will be a pointer to the node. 
        *                    If the node exists, it will return that pointer. If not, it will return NULL.
        * Function Efficiency: The algorithm will have a runtime of O(n), 
        *                    since the worst case will be visiting every node in the graph.
        */
        vector<Airport> BFS(int source, int destination);

        /* 
        * colorGraph: Assign different color values to the attributes of the graph nodes.
        * Function Inputs: A graph based on the relationships listed in the OpenFlight Data.
        * Function Outputs: A mapping of airports to colors
        * Function Efficiency: The greedy coloring algorithm will have a runtime complexity of O(n^2), 
        * since we need to visit every vertices and color every vertices that it is adjacent to.
        */
        map<int, int> colorGraph(map<int, vector<int>> graph);
        
        /* 
        * Dijkstra: Find the smallest distance between two airports.
        * Function Inputs: Two nodes (airports) we are trying to find the shortest path between. 
        *                  Weights for all of our edges are the geographic distance between airports.
        * Function Outputs: The length of the shortest path, which represents the number of edges in the shortest path.
        * Function Efficiency: Time complexity of Dijkstra's algorithm is O(n^2) as given in the definition of the algorithm.
        */
        vector<int> Dijkstra(int sourceID, int destID);

    private:
        vector<Airport> bfs_out;
        map<int, Airport> airports_;
        vector<Flights> routes_;
        map<int, vector<int>> adj_list;
};
