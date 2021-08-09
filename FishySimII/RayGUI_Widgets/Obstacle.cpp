#include "Obstacle.h"

Obstacle::Obstacle() {
	mPosition = {0, 0};
	mRadius = 1.0f;
}

Obstacle::Obstacle(Vector2 pos, float rad) {
	mPosition = pos;
	mRadius = rad;
}

Obstacle::~Obstacle() {}