# asuthi3-rayli2-jiyanxu2-shiqiy2

## Data
All data can be found inside the resource folder. The airport.dat contains the information about each airport, and the routes connecting airports are in the routes.dat. The template.txt provides metadata for both the airports and the routes.

## Build and run program
Use "make" to make an executable file relating to main. Use "make test" to make executable test file with test.cpp. Use ./main to run main file and ./test to run test file. All test file are included inside the "tests" folder. 

## How To Run Main Function
Run "./main" to run the main function. Our main function only contains the shortest path algorithm. The user may enter two airport ID's and our program will return the shortest path between the airports if it exists. Enter valid inputs when prompted. Invalid inputs will result in error messages. 

## Test Cases
All test cases are in the test.cpp in the tests folder. We have test cases for all three algorithms implemented (BFS, Dijkstra, Greedy Graph Coloring) as well as basic functionality of the graph implementation.

## Changes to the Dataset
To have better parsing results, we deleted all commas within quotations in each line of our airport.dat. For example, if a data line used to be (146,"Bob's International Airport, and restaurant","Paris","Canada","YUL","CYUL",45.4706001282,-73.7407989502,118,-5,"A","America/,Toronto","ai,rport","Our,Airports"), it would be changed to (146,"Bob's International Airport and restaurant","Paris","Canada","YUL","CYUL",45.4706001282,-73.7407989502,118,-5,"A","America/Toronto","ai,rport","OurAirports").

## Graph Construction
Our graph only recognizes connections between airports if there are flights both ways. For example, if there is a flight from Chicago to Denver and from Denver to Chicago, there would be an edge connecting the two cities. However if there is only one flight from Chicago to Denver and not the other way around, there would be no edge connecting the two cities.
