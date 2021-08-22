#pragma once
#include <iostream>
#include <vector>
#include "PathFinding.h"

using std::vector;

class GridMap {
public: ///Public Variables
	static const int gridSpacing = 20;

	static const int mapWidth = 64;
	static const int mapHeight = 36;
	Node* map[mapHeight][mapWidth]; //36 rows + 64 collumns


public:
	void DrawGrid(Color COLOR);
	void DrawIntersects(Color COLOR);

	void DrawNodes(Color COLOR);
	void DrawNode(Node* node, bool selected);
};

