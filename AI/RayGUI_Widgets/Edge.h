#pragma once
#include "raylib.h"
#include <vector>

using std::vector;

class Node;
class Edge {
private: /// Private Variables ///
	Node* mParent;
	Node* mNeighbour;
	int gCost;
	int hCost;

public: /// Public Functions ///
	Edge(Node* target, int gCost);
	~Edge();

	/* Get */
	inline Node* GetParent() { return mParent; }
	inline Node* GetNeighbour() { return mNeighbour; }
	inline int GetGCost() { return gCost; }
	inline int GetHCost() { return hCost; }

	/* Set */
	inline void SetParent(Node* parent) { mParent = parent; }
	inline void SetNeighbour(Node* target) { mNeighbour = target; }
	inline void SetGCost(int g) { gCost = g; }
	inline void SetHCost(int h) { hCost = h; }
};

