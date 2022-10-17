#include "graph.h"
using namespace std;


// Constructor
Graph::Graph(string airport_directory, string routes_directory) {
    parse_airport(airport_directory);
    parse_routes(routes_directory);
    make_adj();
}

/* 
 * file_parser: Parse the data from a .dat file.
 * Function Inputs: The directory of a .dat file containing all information seperated by "," and newlines
 * Function Outputs: A vector of vector - vector<vector<string>>
 *                  where each vector represents all information needed 
 *                  to construct an object (such as airports, flights, etc.).
 */
vector<vector<string>> Graph::file_parser(string directory) {
    ifstream datafile;
    datafile.open(directory);

    // airport stores every line seperated by ","
    vector<string> airport;
    vector<vector<string>> all_airport;

    if (datafile.is_open()) {
      string line;
      while(getline(datafile, line)){

        string airport_property = "";
        for (auto x : line) {
          if (x == ',') {
            // push the property when "," encountered
            airport.push_back(airport_property);
            airport_property = "";
          } else {
            if (x != '\"') {
                airport_property = airport_property + x;
            }
          }
        }
        // add the current airport to ret and clear it
        all_airport.push_back(airport);
        airport.clear();
      }
    } else {
        cout<< "Fail to open the file!" <<endl;
    }

    datafile.close();
    return all_airport;
}

// Creates and Adjecency List from data in airports_ and routes_
void Graph::make_adj() {
    for (auto it : airports_) {
        int airportID = it.first;
        vector<int> edges;
        for (auto flight : routes_) {
            if (flight.getSourceAirportID() == airportID) {
                edges.push_back(flight.getDestinationAirportID());
            }
            
        }
        sort(edges.begin(), edges.end());
        adj_list.insert(pair<int, vector<int>>(airportID, edges));
    }
}

// Turns String Data into Airport Objects
void Graph::parse_airport(string directory) {
    vector<vector<string>> all_airport = file_parser(directory);
    for (auto x : all_airport) {
        try {
          Airport a(x[1], stoi(x[0]), x[2], x[3], stod(x[6]), stod(x[7]));
          pair<int, Airport> p(stoi(x[0]), a);
          airports_.insert(p);
        } catch (...) {
          cout << x[0] << " " << x[1] << " " << stoi(x[0]) << " " << x[2] << " " << x[3] << " " << x[6] << " " << x[7] << endl;
        }
    }
}

// Turns String Data into Flight Objects
void Graph::parse_routes(string directory) {
    vector<vector<string>> all_routes = file_parser(directory);
    for (auto x : all_routes) {
        int source_id = -1;
        int des_id = -1;
        if (x[3] != "\\N") source_id = stoi(x[3]);
        if (x[5] != "\\N") des_id = stoi(x[5]);

        if(airports_.find(source_id) != airports_.end() && airports_.find(des_id) != airports_.end()){
            Airport source = airports_[source_id];
            Airport des = airports_[des_id];
            Flights f(x[0], x[1], source, des);
            routes_.push_back(f);
        }
    }
}


/// Getters
map<int, vector<int>> Graph::getAdj() {
    if (adj_list.empty()) return map<int, vector<int>>();
    return adj_list;
}
map<int, Airport> Graph::getAirports() {
    return airports_;
}
vector<Flights> Graph::getRoutes() {
    return routes_;
}

/* 
 * Find: A private method implemented for BFS.
 * Function Inputs: The airportID of the airport we are trying to find. 
 * Function Outputs: Return true if found, return false if not found.
 * Function Efficiency: The algorithm will have a runtime of O(n), 
 *                    since the worst case will be visiting every node in the graph.
 */
bool Graph::Find(int id) {
  bfs_out = BFS(1,-1);
    try {
      for (auto something : bfs_out) {
        if (something.getAirportID() == id) {
          return true;
        }
      }
    } catch (...) {
      cout << "BROKEN" << endl;
    }
    return false;
}

/* 
 * BFS: Traverse the whole graph and find whether there exists an airport with the same ID as source airport.
 * Function Inputs: Two airport IDs we are trying to find the shortest path between. 
 * Function Outputs: The output will be a pointer to the node. 
 *                    If the node exists, it will return that pointer. If not, it will return NULL.
 * Function Efficiency: The algorithm will have a runtime of O(n), 
 *                    since the worst case will be visiting every node in the graph.
 */
vector<Airport> Graph::BFS(int source, int destination) {
    if (source == destination) { return {airports_[source]}; }
    vector<bool> visited(14110, false);
    queue<int> queue;

    vector<Airport> result;

    queue.push(source);

    if (adj_list.find(source) == adj_list.end()) return result;

    int current = queue.front();
    try {
      while (!queue.empty()) {
            current = queue.front();
            if (visited[current]) {
              queue.pop();
              continue;
            }

            for (int adj : adj_list.find(current)->second) {
                queue.push(adj);
            }
            result.push_back(airports_.find(current)->second);
            visited[current] = true;   

            queue.pop();
            if (current == destination) break;
      }
    } catch (...) {
      cout << current << endl;
      cout << "visited_size: " << visited.size() << endl;
    }

    return result;
}

/* 
 * colorGraph: Assign different color values to the attributes of the graph nodes.
 * Function Inputs: A graph based on the relationships listed in the OpenFlight Data.
 * Function Outputs: A mapping of airports to colors
 * Function Efficiency: The greedy coloring algorithm will have a runtime complexity of O(n^2), 
 * since we need to visit every vertices and color every vertices that it is adjacent to.
 */
map<int, int> Graph::colorGraph(map<int, vector<int>> graph) {
  map<int, int> colored_graph;
  for (auto airport : graph) {
    vector<int> colors;
    for (int color = 0; color < (int)graph.size(); color++) {
      colors.push_back(color);
    }
    for (size_t neighbor = 0; neighbor < airport.second.size(); neighbor++) {
      map<int, int>::const_iterator lookup_airport = colored_graph.find(airport.second[neighbor]);
      if (lookup_airport != colored_graph.end()) {
        colors[lookup_airport -> second] = -1;
      }
    }
    for (size_t i = 0; i < colors.size(); i++) {
      if (colors[i] != -1) {
        colored_graph.insert(pair<int, int>(airport.first, colors[i]));
        break;
      }
    }
  }
  return colored_graph;
}

/* 
 * Dijkstra: Find the smallest distance between two airports.
 * Function Inputs: Two nodes (airports) we are trying to find the shortest path between. 
 *                  Weights for all of our edges are the geographic distance between airports.
 * Function Outputs: The length of the shortest path, which represents the number of edges in the shortest path.
 * Function Efficiency: Time complexity of Dijkstra's algorithm is O(n^2) as given in the definition of the algorithm.
 */
vector<int> Graph::Dijkstra(int sourceID, int destID) {
    if (adj_list[sourceID].empty()) {return vector<int>();}
    if (adj_list[destID].empty()) {return vector<int>();}
    // if (Find(sourceID)) return vector<int>();
    vector<int> path; // the actual path with nodes
    stack<int> reverse_path;
    // *Note: C++ 11 does not support variable sized arrays
    // double distance[adj_list.size()] = {99999999.99}; // distance vector
    vector<double> dist(adj_list.size(), INFINITY);
    
    priority_queue<pair<int, int>, vector< pair<int, int> >, greater<pair<int, int> >> pq; // priority queue used to determine order of accessing
    vector<bool> visited(adj_list.size(), false); // visited list
    map<int,pair<int,double>> reverse_shortest; // a map to traceback the shortest path
    
    dist[sourceID] = 0.00;  
    pq.push(make_pair(sourceID,0));
    while(!pq.empty()){
      int vertice = pq.top().first;
      pq.pop();
      vector<int> adj = adj_list[vertice];
      
      for(size_t i = 0; i < adj.size(); i++){
            int adjacent_vertice = adj[i];
            int weight = airports_[vertice].calculateWeights(airports_[adjacent_vertice]);
            
            // If the distance to v is shorter by going through u...
            if(dist[adjacent_vertice] > dist[vertice] + weight){
                // Update the distance of v.
                dist[adjacent_vertice] = dist[vertice] + weight;
                // Insert v into the pq. 
                pq.push(make_pair(adjacent_vertice, dist[adjacent_vertice]));
                reverse_shortest[adjacent_vertice] = make_pair(vertice,dist[adjacent_vertice]);
            }
      }
    }

    // put reverse order into stack
    int key = destID;
    reverse_path.push(destID);
    while(key != sourceID){
      
      key = reverse_shortest[key].first;
      reverse_path.push(key);
    }

    // put order back together
    while(!reverse_path.empty()){
      path.push_back(reverse_path.top());
      reverse_path.pop();
    }

    return path;
}
