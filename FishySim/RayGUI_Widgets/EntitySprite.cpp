#include "EntitySprite.h"

EntitySprite::EntitySprite() {}
EntitySprite::~EntitySprite() {}

void EntitySprite::Start() {}
void EntitySprite::Update() {}

/* Render the fish sprite */
void EntitySprite::Draw() {
	DrawPoly(EntityObject::GetPos(), 5, 20, 45, MAGENTA);

	float angleH = atan2(EntityObject::GetPosL().m7, EntityObject::GetPosL().m8);
	float angleL = angleH + 0.3 + PI / 2;
	float angleR = angleH - 0.3 - PI / 2;

	Vector2 head = {
		10 * cos(angleH) + GetPos().x,
		10 * sin(angleH) + GetPos().y,
	};
	Vector2 tailL = {
		2 * cos(angleL) + GetPos().x,
		2 * sin(angleL) + GetPos().y,
	};
	Vector2 tailR = {
		2 * cos(angleR) + GetPos().x,
		2 * sin(angleR) + GetPos().y,
	};

	// Draw the fishies
	DrawTriangle(head, tailR, GetPos(), Color{ 255, 161, 0, 100 });
	DrawTriangle(head, GetPos(), tailL, Color{ 190, 33, 55, 100 });

	DrawTriangleLines(head, tailR, GetPos(), ORANGE);
	DrawTriangleLines(head, GetPos(), tailL, MAROON);
}