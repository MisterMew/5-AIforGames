#include "PathFinding.h"

/* 
* Add distances between every node
* Add heuristic (smelly cheese) 
* P(v) = dist(v) + h(v)
*  P: priority for priority queue
*  which is the distance + the heuristic
*/

bool PathFind::NodeSort(Node* i, Node* j) { //Use this function to sort nodes using their gScore value
	return (i->GetGScore() < j->GetGScore());
}

vector<Node*> PathFind::FindPath(Node* startNode, Node* endNode) {
	if (startNode == nullptr || endNode == nullptr) { return vector<Node*>(); } //Validate the input

	if (startNode == endNode) {
		vector<Node*> singleNodePath;
		singleNodePath.push_back(startNode);
		return singleNodePath;
	}

	//Initialize the starting node
	startNode->SetGScore(0);
	startNode->previous = nullptr;

	vector<Node*> openList;			 //List for nodes open to evaluation
	vector<Node*> closedList;		//List for nodes already evaluated
	openList.push_back(startNode); //Add the starting node to openList

	while (!openList.empty()) {
		Node* currentNode = openList.front(); //Set the current node to the first node in the openList

		for (int i = 0; i < openList.size(); i++) { //Get the node with the lowest fCost
			if (openList[i]->GetFScore() < currentNode->GetFScore() || openList[i]->GetFScore() == currentNode->GetFScore() && openList[i]->GetHScore() < currentNode->GetHScore()) {
				currentNode = openList[i];
			}
		}

		openList.erase(openList.begin());   //Remove currentNode from openList
		closedList.push_back(currentNode); //Add currentNode to closedList

		if (currentNode == endNode) { break; } //If the destination node was added to the closed list, the shortest path has been found

		for (Edge edge : currentNode->connections) { //For each Edge e in currentNode's connections

		}








		 
		std::sort(openList.begin(), openList.end(), &NodeSort); //Sort openList based on gScore using the function created above
		
		Node* currentNode = openList.front(); //Set the current node to the first node in the openList
		openList.erase(openList.begin());    //Remove currentNode from openList
		closedList.push_back(currentNode);  //Add currentNode to closedList
		
		if (currentNode == endNode) { break; }	   //If the destination node was added to the closed list, the shortest path has been found
		for (Edge e : currentNode->connections) { //For each Edge e in currentNode's connections
			if (std::find(closedList.begin(), closedList.end(), e.target) != closedList.end()) {
				continue; //If the target node is in the closedList, ignore it
			}
			
			if (std::find(openList.begin(), openList.end(), e.target) == openList.end()) { //If the target node is not in the openList, update it
				
				e.target->SetGScore( currentNode->GetGScore() + e.cost ); //Calculate the target node's G Score
				e.target->previous = currentNode;				//Set the target node's previous to currentNode
				
				auto insertionPos = openList.end(); //Find the earliest point we should insert the node to the list to keep it sorted
				for (auto i = openList.begin(); i != openList.end(); i++) {
					if (e.target->GetGScore() < (*i)->GetGScore()) {
						insertionPos = i;
						break;
					}
				}
				openList.insert(insertionPos, e.target); //Insert the node at the appropriate position
			}
			
			else { //Otherwise the target node IS in the open list
				if (currentNode->GetGScore() + e.cost < e.target->GetGScore()) { //Compare the new G Score to the old one before updating
					e.target->SetGScore( currentNode->GetGScore() + e.cost );  //Calculate the target node's G Score
					e.target->previous = currentNode;				 //Set the target node's previous to currentNode
				}
			}
		}
	}
	//Create path in reverse from endNode to startNode
	vector<Node*> path;
	Node* currentNode = endNode;

	while (currentNode != nullptr) {
		path.insert(path.begin(), currentNode); //Add the current node to the beginning of the path
		currentNode = currentNode->previous;   //Go to the previous node
	}
	return path;
}




void PathFind::DrawGraph(Node* node, std::vector<Node*>* drawnList) {
	DrawNode(node);
	drawnList->push_back(node);

	//For each Edge in this node's connections
	for (Edge e : node->connections) {
		DrawLine(node->mPosition.x, node->mPosition.y, e.target->mPosition.x, e.target->mPosition.y, WHITE); //Draw the Edge
		//Draw the cost
		Vector2 costPos = { (node->mPosition.x + e.target->mPosition.x) / 2, (node->mPosition.y + e.target->mPosition.y) / 2 };
		static char buffer[10];
		sprintf_s(buffer, "%.0f", e.cost);
		DrawText(buffer, costPos.x, costPos.y, 15, WHITE);
		//Draw the target node
		if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end())
		{
			DrawGraph(e.target, drawnList);
		}
	}
}
