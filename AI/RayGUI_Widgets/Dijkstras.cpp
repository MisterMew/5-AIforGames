#include "Dijkstras.h"

namespace dijkstras {
	//Use this function to sort nodes using their gScore value
	bool NodeSort(Node* i, Node* j) {
		return (i->gScore < j->gScore);
	}

	vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode) {
		if (startNode == nullptr || endNode == nullptr) { //Validate the input
			return vector<Node*>();
		}

		if (startNode == endNode) {
			vector<Node*> singleNodePath;
			singleNodePath.push_back(startNode);
			return singleNodePath;
		}

		//Initialize the starting node
		startNode->gScore = 0;
		startNode->previous = nullptr;

		//Create our temporary lists for storing nodes
		vector<Node*> openList;
		vector<Node*> closedList;

		//Add the starting node to openList
		openList.push_back(startNode);

		while (!openList.empty()) {
			sort(openList.begin(), openList.end(), NodeSort); //Sort openList based on gScore using the function created above

			Node* currentNode = openList.front(); //Set the current node to the first node in the openList
			openList.erase(openList.begin());    //Remove currentNode from openList
			closedList.push_back(currentNode);  //Add currentNode to closedList

			//If the destination node was added to the closed list, the shortest path has been found
			if (currentNode == endNode) { break; }

			for (Edge e : currentNode->connections) { //For each Edge e in currentNode's connections
				
				if (std::find(closedList.begin(), closedList.end(), e.target) != closedList.end()) {
					continue; //If the target node is in the closedList, ignore it
				}
				
				if (std::find(openList.begin(), openList.end(), e.target) == openList.end()) { //If the target node is not in the openList, update it
					
					e.target->gScore = currentNode->gScore + e.cost; //Calculate the target node's G Score
					e.target->previous = currentNode;				//Set the target node's previous to currentNode
					
					auto insertionPos = openList.end(); //Find the earliest point we should insert the node to the list to keep it sorted
					for (auto i = openList.begin(); i != openList.end(); i++) {
						if (e.target->gScore < (*i)->gScore) {
							insertionPos = i;
							break;
						}
					}
					
					openList.insert(insertionPos, e.target); //Insert the node at the appropriate position
				}
				
				else { //Otherwise the target node IS in the open list
					if (currentNode->gScore + e.cost < e.target->gScore) { //Compare the new G Score to the old one before updating
						e.target->gScore = currentNode->gScore + e.cost;  //Calculate the target node's G Score
						e.target->previous = currentNode;				 //Set the target node's previous to currentNode
					}
				}
			}
		}

		//Create path in reverse from endNode to startNode
		std::vector<Node*> path;
		Node* currentNode = endNode;

		while (currentNode != nullptr)
		{
			//Add the current node to the beginning of the path
			path.insert(path.begin(), currentNode);
			//Go to the previous node
			currentNode = currentNode->previous;
		}

		return path;
	}

	 /// DRAW: Node
	/* Draws the node */
	void DrawNode(Node* node, bool selected) {
		static char buffer[10];
		sprintf_s(buffer, "%.0f", node->gScore);

		//Draw the circle for the outline
		DrawCircle(node->position.x, node->position.y, 25, YELLOW);
		//Draw the inner circle
		if (selected) {
			DrawCircle(node->position.x, node->position.y, 22, BROWN);
		}
		else {
			DrawCircle(node->position.x, node->position.y, 22, BLACK);
		}
		//Draw the text
		DrawText(buffer, node->position.x - 10, node->position.y - 10, 15, WHITE);
	}

	void DrawGraph(Node* node, std::vector<Node*>* drawnList)
	{
		DrawNode(node);
		drawnList->push_back(node);

		//For each Edge in this node's connections
		for (Edge e : node->connections)
		{
			//Draw the Edge
			DrawLine(node->position.x, node->position.y, e.target->position.x, e.target->position.y, WHITE);
			//Draw the cost
			Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
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
}