#pragma once
#include <iostream>
#include <vector>
#include "Dijkstras.h"

using namespace dijkstras;
using std::vector;

class GridMap {
public: ///Public Variables
	static const int mapWidth = 2;
	static const int mapHeight = 2;
	Node* map[mapHeight][mapWidth]; //36 rows + 64 collumns

	static const int spacing = 20;

public:
	void DrawGrid(Color COLOR);
	void DrawNodes(Color COLOR);
	void DrawNodes(vector<Node*> nodes);
};

