#pragma once
#include "raylib.h"

#include "GridMap.h"
#include "Node.h"
#include "Edge.h"

#include <algorithm>
#include <vector>
#include <cmath>
#include <list>

using std::vector;

class Node; 
class Edge;
class GridMap;
class PathFind {
private: /// Private Variables ///
	const int diagonalDist = 14;
	const int axialDist = 10;

private: /// Private Functions ///
	bool NodeSort(Node* i, Node* j);

public:  /// Public Functions ///
	vector<Node*> FindPath(Node* startNode, Node* endNode);
	int GetDistance(Node* nodeA, Node* nodeB);
	void RetracePath(Node* startNode, Node* endNode);
};