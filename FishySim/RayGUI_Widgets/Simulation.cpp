#include "simulation.h"

void Entity::UpdateEntity() {
	//Wrap SCreen
	if (GetPos().x < 0) { mPosition.x = GetScreenWidth(); }
	if (GetPos().y < 0) { mPosition.y = GetScreenHeight(); }
	if (GetPos().x > GetScreenWidth()) { mPosition.x = 0; }
	if (GetPos().y > GetScreenHeight()) { mPosition.y = 0; }

	// Moves the entities
	mPosition.x += GetVel().x;
	mPosition.y += GetVel().y;
}

void Entity::RenderFish() {
	float angleH = atan2(GetVel().y, GetVel().x);
	float angleL = angleH + 0.3 + PI / 2;
	float angleR = angleH - 0.3 - PI / 2;

	Vector2 head = {
		(mSize * 15) * cos(angleH) + GetPos().x,
		(mSize * 15) * sin(angleH) + GetPos().y,
	};
	Vector2 tailL = {
		(mSize * 5) * cos(angleL) + GetPos().x,
		(mSize * 5) * sin(angleL) + GetPos().y,
	};
	Vector2 tailR = {
		(mSize * 5) * cos(angleR) + GetPos().x,
		(mSize * 5) * sin(angleR) + GetPos().y,
	};

	// Draw the fishies
	DrawTriangle(GetPos(), tailR, tailL, RAYWHITE);
	
	DrawTriangle(head, tailR, GetPos(), Color{255, 161, 0, 100});
	DrawTriangle(head, GetPos(), tailL, Color{190, 33, 55, 100});
	
	DrawTriangleLines(head, tailR, GetPos(), ORANGE);
	DrawTriangleLines(head, GetPos(), tailL, MAROON);
}

void Entity::EntityDetection() {
}