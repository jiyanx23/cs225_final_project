# Leading Question

What is the shortest path between two given airports?

There are a lot of things we can learn from the Open Flights dataset. We can learn about the routes the different airlines travel, or how different airports connect to one another, or how far different airports are from each other. Here, we are hoping to solve: "what is the shortest flight path from airport A to airport B?" as our leading question. To do this we will be using the OpenFlights datasets, more specifically the airport and routes data sets. We will have to parse through the .DAT file and create a graph, then create a find algorithm to find specific nodes on the graph we have created, then also create the shortest distance algorithm or the Dijkstra's Algorithm. With that we can use the shortest distance algorithm on the graph between two nodes to find the shortest distance or shortest number of connections. Which all helps answer our question. 

# Data Collection

The input dataset will be using OpenFlights specifically, the airport.dat and routes.dat which total around roughly ~2.4 MB in size. We plan to use all the data if possible but if there are any loading time problems then will switch to a smaller subset, this subset might be defined as to have a limit of countries and states. 

We will parse the data through looking at each line in the downloaded DAT file and creating a node object containing the data of: Airport ID, Name, City, Country, Latitude, and Longitude. Some checks that will be put in place during this process of data acquisition would be creating a correctness checking method that compares the nodes created to a provided DAT from the downloaded file. We will also use a small subset of the data to check for the initial graph structure build up by passing those values into test cases after the graph is constructed.

The data structure we are going to be using to store the data within our code would be a custom object or structure that contains variables that correspond to the information from the DAT. The object or structure will also contain a vector of edges that corresponds to what the node is connected to. With all this in mind we believe that the space complexity O(nodes + edges).

# Graph Algorithms

## Find Algorithm

Function Inputs: We will need to create a graph based on the data provided. The inputs for this algorithm will be the airport ID. The algorithm will traverse the whole graph, and find whether there exists an airport that has the exact same ID. Specifically, we will be implementing using the BFS traversal method (traverse by going through a path through adjacent nodes and then backtrack). Since the find algorithm will be a private method that helps us to implement other methods, we choose to use airport ID instead of other “user friendly” fields.

Function Outputs: The output will be a pointer to the node. If the node exists, it will return that pointer. If not, it will return NULL.

Function Efficiency: The algorithm will have a runtime of O(n), since the worst case will be visiting every node in the graph. 
	

## Dijkstra's Algorithm:

Function Inputs: We first need to create a graph based on the relationship indicated in the OpenFlight data. The edges between nodes represent flights. Dijkstra's Algorithm will be used to find the smallest distance between two airports. The input of the algorithm are the two nodes (airports) we are trying to find the shortest path between. We will be using the geographic distance between airports as the weights for all of our edges.

Function Outputs: We will output the length of the shortest path, which represents the number of edges in the shortest path.

Function Efficiency: The time complexity of Dijkstra's algorithm is O(n^2) as given in the definition of the algorithm.



## Greedy Coloring Algorithm

Function Inputs: We first need to create a graph based on the relationships listed in the OpenFlight Data. The algorithm will visit every vertices in the graph using welsh-powell algorithm to determine the order of coloring. There won’t be any input for the function, instead, the function will assign different color values to the attributes of the graph node itself.

Function Outputs: The function will print out the result of the coloring for each vertices.


Function Efficiency: The greedy coloring algorithm will have a runtime complexity of O(n^2), since we need to visit every vertices and color every vertices that it is adjacent to.

# Timeline
3.25.2022 - 4.1.2022		Data Collection and Format (construct graph)

4.2.2022 - 4.9.2022 		Implement Find Algorithm

4.9.2022 - 4.23.2022 		Implement Dijkstra’s Algorithm and Greedy Coloring Algorithm

4.23.2022 - 4.30.2022		Create and Deliver Final Presentation of Project

