#include "EntityObstacle.h"

Obstacle::Obstacle() : Obstacle({ 0, 0 }) {}

Obstacle::Obstacle(Vector2 pos) {
	SetPos(pos);
}

Obstacle::~Obstacle() {}

 /// DRAW: Obstacle
/* Draws the sprite for the obstacle */
void Obstacle::Draw() {
	//DrawRectangle(GetPos().x, GetPos().y, GetSize(), GetSize(), BLACK);
	DrawRectanglePro({ GetPos().x, GetPos().y, (float)GetSize(), (float)GetSize() }, Vector2({ (float)GetSize() / 2, (float)GetSize() / 2 }), 0, BLACK);
}