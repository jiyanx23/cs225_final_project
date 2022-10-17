# Dev Log week 3 (4/8 - 4/15)
This week we were able to successfully parse through all of our data and sort it out. We also created a function to find weights (distance) of each flight as well as created the objects that represent our flights graph. Additionally, we also started developing an implementation for Dijkstra’s Algorithm although we do not currently have our graph fully developed so our Dijkstra’s does not completely work.


This week we also had some difficulties with our class implementations. We had problems because our flights class and our airports class depended on each other creating a circular dependency. The calculate weights function in our flights class took two airport objects as inputs and calculated the weight of the edge between them. However, we also had a vector of flights in the airport class that stored all the flights that originated from that airport. We are still currently working on this problem.

Though we are delayed, next week we hope to finish our find algorithm that uses BFS traversal. 
