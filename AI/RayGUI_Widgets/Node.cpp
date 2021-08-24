#include "Node.h"

Node::Node() {}
Node::Node(Vector2 pos, Vector2 gridPos) {
	SetPos(pos);
	SetGridPos(gridPos);
}
Node::Node(Node* position, int gCost) {
	SetPos({ position->GetGridPos() });
	SetGCost(gCost);
}
Node::~Node() {}