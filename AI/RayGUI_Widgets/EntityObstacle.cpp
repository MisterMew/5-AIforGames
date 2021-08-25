#include "EntityObstacle.h"

Obstacle::Obstacle() : Obstacle({ 0, 0 }) {}

Obstacle::Obstacle(Vector2 pos) {
	SetPos(pos);
}

Obstacle::~Obstacle() {}

void Obstacle::Draw() {
	DrawRectangle(GetPos().x, GetPos().y, GetSize(), GetSize(), BLACK);
}