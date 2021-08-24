#pragma once
#include "raylib.h"
#include "Edge.h"
#include <iostream>
#include <vector>

using std::vector;

class Edge;
class Node {
private: /// Private Variables ///
	int gCost;
	int hCost;
	int fCost;

	Vector2 mPosition; // x, y // Global position
	Vector2 mGridPos; // h, w // Grid Position

public: /// Public Variables ///
	Node* previous;
	Node* targetNode;
	vector<Edge> connections;

public: /// Public Functions ///
	Node();
	Node(Vector2 pos, Vector2 gridPos);
	Node(Node* position, int gCost);
	~Node();

	/* Get */
	inline int GetGCost() { return gCost; }
	inline int GetHCost() { return hCost; }
	inline int GetFCost() { return gCost + hCost; }

	inline Vector2 GetPos() { return mPosition; }
	inline Vector2 GetGridPos() { return mGridPos; }

	/* Set */
	inline void SetGCost(int g) { gCost = g; }
	inline void SetHCost(int h) { hCost = h; }
	inline void SetFCost() { fCost = GetFCost(); }

	inline void SetPos(Vector2 position) { mPosition = position; }
	inline void SetGridPos(Vector2 gridPos) { mGridPos = gridPos; }
};

