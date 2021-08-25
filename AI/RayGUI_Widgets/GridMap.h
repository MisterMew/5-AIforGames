#pragma once

#include "CustomColours.h"
#include "PathFinding.h"
#include "raymath.h"
#include "Node.h"

#include <iostream>
#include <vector>

using std::vector;

class GridMap {
private: /// Private Variables
	static const int gridSpacing = 20;
	const int axialDist = 10;

public: /// Public Variables
	static const int mapWidth = 64;
	static const int mapHeight = 36;
	static Node* map[mapHeight][mapWidth]; //36 rows + 64 collumns //Static class doesn't initialise

	vector<Node*> tempList;

public:
	void CreateGridNetwork();
	void CreateConnections();

	void DrawGrid(Color COLOR);
	void DrawIntersects(Color COLOR);

	void DrawNodes(Color COLOR);
	void DrawPath(Node* startNode, Node* endNode);
	void DrawPath(vector<Node*>& path);

	Vector2 MouseToGrid(Vector2 mousePos);
};