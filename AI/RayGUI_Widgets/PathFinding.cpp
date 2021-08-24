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
		
		if (currentNode == endNode) {		 //If the currentNode is the end/target node
			RetracePath(startNode, endNode);//Retrace the found path,
			break;						   //exit the while loop
		} 
		
		for (Edge connection : currentNode->connections) {																  //For each neighbouring Node in currentNode's connections
			if (find(closedList.begin(), closedList.end(), connection.GetNeighbour()) == closedList.end()) { continue; } //If the neighbour IS in the CLOSED list, continue;
		
			int newCostToNeighbour = currentNode->GetGCost() + GetDistance(currentNode, connection.GetNeighbour());									   //Calculate the cost to reach the neighbouring node
			if (newCostToNeighbour < connection.GetGCost() || find(openList.begin(), openList.end(), connection.GetNeighbour()) != openList.end()) {  //If the neighbour is NOT in the OPEN list, continue;
				connection.SetGCost( newCostToNeighbour);
				connection.SetHCost( GetDistance(connection.GetNeighbour(), endNode));
				connection.SetParent(currentNode);
		
				if (find(openList.begin(), openList.end(), connection.GetNeighbour()) != openList.end()) { //If the neighbour is NOT in the OPEN list, continue;
					openList.push_back(connection.GetNeighbour());
				}
			}
		}
		


		 
		//std::sort(openList.begin(), openList.end(), NodeSort); //Sort openList based on gScore using the function created above
		//
		//Node* currentNode = openList.front(); //Set the current node to the first node in the openList
		//openList.erase(openList.begin());    //Remove currentNode from openList
		//closedList.push_back(currentNode);  //Add currentNode to closedList
		//
		//if (currentNode == endNode) { break; }	   //If the destination node was added to the closed list, the shortest path has been found
		//for (Edge e : currentNode->connections) { //For each Edge e in currentNode's connections
		//	if (std::find(closedList.begin(), closedList.end(), e.GetTarget()) != closedList.end()) {
		//		continue; //If the target node is in the closedList, ignore it
		//	}
		//	
		//	int newCost; ///
		//	if (std::find(openList.begin(), openList.end(), e.GetTarget()) == openList.end()) { //If the target node is not in the openList, update it
		//		
		//		e.GetTarget()->SetGCost( currentNode->GetGCost() + e.GetGCost() ); //Calculate the target node's G Score
		//		e.GetTarget()->previous = currentNode;				//Set the target node's previous to currentNode
		//		
		//		auto insertionPos = openList.end(); //Find the earliest point we should insert the node to the list to keep it sorted
		//		for (auto i = openList.begin(); i != openList.end(); i++) {
		//			if (e.GetTarget()->GetGCost() < (*i)->GetGCost()) {
		//				insertionPos = i;
		//				break;
		//			}
		//		}
		//		openList.insert(insertionPos, e.GetTarget()); //Insert the node at the appropriate position
		//	}
		//	
		//	else { //Otherwise the target node IS in the open list
		//		if (currentNode->GetGCost() + e.GetGCost() < e.GetTarget()->GetGCost()) { //Compare the new G Score to the old one before updating
		//			e.GetTarget()->SetGCost( currentNode->GetGCost() + e.GetGCost());   //Calculate the target node's G Score
		//			e.GetTarget()->previous = currentNode;						   //Set the target node's previous to currentNode
		//		}
		//	}
		//}
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
void PathFind::RetracePath(Node* startNode, Node* endNode) {
	vector<Node*> path;
	Node* currentNode = endNode;

	while (currentNode != startNode) {
		path.insert(path.begin(), currentNode); //Add the current node to the beginning of the path
		currentNode = currentNode->previous;   //Go to the previous node
	}

	grid.DrawPath(startNode, endNode);
}
