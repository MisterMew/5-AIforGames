#pragma once
#include "raylib.h"
#include <vector>

using std::vector;

class Node;
class Edge {
public: /// Public Variables ///
	Node* target;
	float cost;
};

