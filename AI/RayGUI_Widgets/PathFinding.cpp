#include "PathFinding.h"
GridMap grid;

 /// Sort Nodes
/* Sort the gCost of two nodes */
bool PathFind::NodeSort(Node* i, Node* j) { //Use this function to sort nodes using their gScore value
	return (i->GetGCost() < j->GetGCost());
}

 /// PATH-FINDING
/* A* pathfinding algorithm (modified from AIE Samples) */
vector<Node*> PathFind::FindPath(Node* startNode, Node* endNode) {
	if (startNode == nullptr || endNode == nullptr) { return vector<Node*>(); } //Validate the input

	if (startNode == endNode) {
		vector<Node*> singleNodePath;
		singleNodePath.push_back(startNode);
		return singleNodePath;
	}

	startNode->SetGCost(0);				//Initialize starting node gCost
	startNode->previous = nullptr;	   //Initialise starting node, previous node

	vector<Node*> openList;			 //List for nodes open to evaluation
	vector<Node*> closedList;		//List for nodes already evaluated
	openList.push_back(startNode); //Add the starting node to openList

	while (!openList.empty()) {
		Node* currentNode = openList.front(); //Set the current node to the first node in the openList
		
		for (unsigned int i = 0; i < openList.size(); i++) { //Get the node with the lowest fCost
			if (openList[i]->GetFCost() < currentNode->GetFCost() || openList[i]->GetFCost() == currentNode->GetFCost() && openList[i]->GetHCost() < currentNode->GetHCost()) {
				currentNode = openList[i];
			}
		}
		
		openList.erase(openList.begin());   //Remove currentNode from openList
		closedList.push_back(currentNode); //Add currentNode to closedList
		
		if (currentNode == endNode) {				 //If the currentNode is the end/target node
			return RetracePath(startNode, endNode); //Retrace the found path,
		} 
		
		for (Edge connection : currentNode->connections) {																  //For each neighbouring Node in currentNode's connections
			if (find(closedList.begin(), closedList.end(), connection.GetNeighbour()) != closedList.end()) { continue; } //If the neighbour is NOT in the CLOSED list, continue;
		
			int newCostToNeighbour = currentNode->GetGCost() + GetDistance(currentNode, connection.GetNeighbour());									  //Calculate the cost to reach the neighbouring node
			if (newCostToNeighbour < connection.GetGCost() || find(openList.begin(), openList.end(), connection.GetNeighbour()) == openList.end()) { //If the neighbour is NOT in the OPEN list, continue;
				connection.SetGCost( newCostToNeighbour);
				connection.SetHCost( GetDistance(connection.GetNeighbour(), endNode));
				connection.SetParent(currentNode);
				connection.GetNeighbour()->previous = currentNode;
		
				if (find(openList.begin(), openList.end(), connection.GetNeighbour()) == openList.end()) { //If the neighbour is NOT in the OPEN list, continue;
					openList.push_back(connection.GetNeighbour());
				}
			}
		}
	}
}

 /// Get Distance
/* Get the distance between two nodes */
int PathFind::GetDistance(Node* nodeA, Node* nodeB) {
	int distX = (int)abs( nodeA->GetGridPos().x - nodeB->GetGridPos().x);
	int distY = (int)abs( nodeA->GetGridPos().y - nodeB->GetGridPos().y);

	if (distX > distY) { return (diagonalDist * distY) + axialDist*(distX - distY); }
	return (diagonalDist * distX) + axialDist * (distY - distX);
}

 /// Retrace Path
/* Retrace the found path from end to beggining */
vector<Node*> PathFind::RetracePath(Node* startNode, Node* endNode) {
	vector<Node*> path;
	Node* currentNode = endNode;

	while (currentNode != nullptr) {
		path.insert(path.begin(), currentNode); //Add the current node to the beginning of the path
		currentNode = currentNode->previous;   //Go to the previous node
	}

	grid.DrawPath(path);
	return path;
}
