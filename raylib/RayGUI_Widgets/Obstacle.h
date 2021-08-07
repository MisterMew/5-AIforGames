#pragma once
#include <raylib.h>

class Obstacle {
private:
	Obstacle();

public:
	Obstacle(Vector2 position, float radius);
	~Obstacle();

	Vector2 mPosition;
	float mRadius;
};