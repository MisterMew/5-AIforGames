#include "Edge.h"

Edge::Edge(Node* target, int gCost) {
	SetNeighbour(target);
	SetGCost(gCost);
}
Edge::~Edge() {}