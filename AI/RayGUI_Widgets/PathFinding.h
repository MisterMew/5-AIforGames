#pragma once
#include "raylib.h"
#include "Node.h"
#include "Edge.h"
#include <vector>
#include <algorithm>

using std::vector;

class Node; 
class Edge;
class PathFind {
private: /// Private Functions ///
	bool NodeSort(Node* i, Node* j);

public:  /// Public Functions ///
	vector<Node*> FindPath(Node* startNode, Node* endNode);
	void DrawNode(Node* node, bool selected = false);
	void DrawGraph(Node* node, std::vector<Node*>* drawnList);

};