#pragma once
#include "raylib.h"
#include <vector>

using std::vector;

class Edge;
class Node {
private: /// Private Variables ///
	int gScore;
	int hScore;
	int fScore;

	int mGridPosX;
	int mGridPosY;

public: /// Public Variables ///
	Vector2 mPosition;
	Node* previous;

	vector<Edge> connections;

public: /// Public Functions ///
	Node();
	Node(Vector2 pos, int gridPosX, int gridPosY);
	~Node();

	/* Get */
	int GetGScore() { return gScore; }
	int GetHScore() { return hScore; }
	int GetFScore() { return gScore + hScore;; }

	/* Set */
	void SetGScore(int g) { gScore = g; }
	void SetHScore(int h) { hScore = h; }
	void SetFScore() { fScore = GetFScore(); }
};

