#include "Node.h"

Node::Node() {}
Node::Node(Vector2 pos, int gridPosY, int gridPosX) {
	mPosition = pos;
	mGridPosY = gridPosY;
	mGridPosX = gridPosX;
}
Node::~Node() {}