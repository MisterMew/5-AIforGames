#include "EntityObstacle.h"

Obstacle::Obstacle() : Obstacle({ 0, 0 }) {}

Obstacle::Obstacle(Vector2 pos) { SetPos(pos); }

Obstacle::~Obstacle() {}

 /// DRAW: Obstacle
/* Draws the sprite for the obstacle */
void Obstacle::Draw() {
	DrawRectanglePro({ GetPos().x, GetPos().y, (float)GetSize(), (float)GetSize() }, Vector2({ (float)GetSize() / 2, (float)GetSize() / 2 }), 0, Color{ 25,25,25,255 });
	DrawRectangleLines(GetPos().x - 10, GetPos().y - 10, GetSize(), GetSize(), Color{20,20,20,255});
}