The application is rather messy as I was more focused on functionality. My apologies.

> PATHFINDING
From 0, 0 to the mouse's position, You will see I have drawn a line of dots.
These dots demonstrate the Astar pathfinding. I have not implemented diagonals.
Due to the the use of a 2D array to create the graph, the pathfinding does prefer to travel vertically before horizontally.

> STATE MACHINE
This does work (evident through the console outputs) and agents do interact with eachother.
The red agents are predators, the green are prey.
The pink circles represent the predators target position.
This is a method I was trying in attempt to align the agents to the grid.

> OBSTACLES
I desperately spent more time then I shouldve trying to get the obstacles to work to further prove my pathfinding was working, 
however I had countless issues trying to delete/disable the relevant nodes and connections.

There are no user inputs, re-running the program wwill place all agents in new positions to see how they intereact in different situations
(it is quite entertaining watching them, despite the simplicity)