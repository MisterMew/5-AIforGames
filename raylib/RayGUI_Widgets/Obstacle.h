#ifndef CIRCLE_H
#define CIRCLE_H

#include <raylib.h>

class Obstacle {
public:
	Obstacle(Vector2 position, float radius);
	~Obstacle();

	Vector2 mPosition;
	float mRadius;

private:
	Obstacle();
};

#endif