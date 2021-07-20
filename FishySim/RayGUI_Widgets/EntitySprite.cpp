#include "EntitySprite.h"
#include "raymath.h"

EntitySprite::EntitySprite() {}
EntitySprite::~EntitySprite() {}

void EntitySprite::Start() {}
void EntitySprite::Update() {}

/* Render the fish sprite */
void EntitySprite::Draw() {
	Vector2 facing = {GetPosG().m7, GetPosG().m8};
	facing = Vector2Normalize(facing);

	float angleH = atan2(( facing.y * GetVel().y), (facing.x * GetVel().x ));
	float angleL = angleH + 0.3 + PI / 2;
	float angleR = angleH - 0.3 - PI / 2;

	Vector2 head = {
		20 * cos(angleH) + GetPos().x,
		20 * sin(angleH) + GetPos().y,
	};
	Vector2 tailL = {
		10 * cos(angleL) + GetPos().x,
		10 * sin(angleL) + GetPos().y,
	};
	Vector2 tailR = {
		10 * cos(angleR) + GetPos().x,
		10 * sin(angleR) + GetPos().y,
	};

	DrawLine(head.x, head.y, head.x + facing.x * 20, head.y + facing.y * 20, MAGENTA);
	DrawLine(head.x, head.y, head.x + GetVel().x * 20, head.y + GetVel().y * 20, PINK);

	// Draw the fishies
	DrawTriangle(head, tailR, GetPos(), Color{ 255, 161, 0, 100 });
	DrawTriangle(head, GetPos(), tailL, Color{ 190, 33, 55, 100 });

	DrawTriangleLines(head, tailR, GetPos(), ORANGE);
	DrawTriangleLines(head, GetPos(), tailL, MAROON);
}