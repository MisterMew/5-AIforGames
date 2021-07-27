#include "EntitySprite.h"

EntitySprite::EntitySprite(SpriteDrawType drawType) : mDrawType(drawType) {}
EntitySprite::~EntitySprite() {}

void EntitySprite::Start() {}
void EntitySprite::Update() {}

/* Render the fish sprite */
void EntitySprite::Draw() {
	if (!HasParent()) { return; }

	switch (mDrawType) {
	case SpriteDrawType::SprFish:
		RenderFish();
		break;

	case SpriteDrawType::SprShark:
		RenderShark();
		break;

	case SpriteDrawType::SprWhale:
		RenderWhale();
		break;

	default: break;
	}
}

  /// RENDER SPRITES
#pragma region [ Sprite Rendering ]
/* Renders the sprite for the FISH */
void EntitySprite::RenderFish() {
	/// Variables
	Vector2 vel = GetParent()->GetVel();

	float angleH = atan2(vel.y, vel.x);
	float angleL = angleH + 0.3 + PI / 2;
	float angleR = angleH - 0.3 - PI / 2;

	/* Calculate Triangle Points */
	Vector2 head = {
		10 * cos(angleH) + GetPos().x,
		10 * sin(angleH) + GetPos().y,
	};
	Vector2 tailL = {
		6 * cos(angleL) + GetPos().x,
		6 * sin(angleL) + GetPos().y,
	};
	Vector2 tailR = {
		6 * cos(angleR) + GetPos().x,
		6 * sin(angleR) + GetPos().y,
	};
	
	/* Draw the fishies */
	DrawTriangle(head, tailR, GetPos(), Color{ 255, 161, 0, 100 });
	DrawTriangle(head, GetPos(), tailL, Color{ 190, 33, 55, 100 });

	DrawTriangleLines(head, tailR, GetPos(), ORANGE);
	DrawTriangleLines(head, GetPos(), tailL, MAROON);

	  /// DEBUG MODE
#ifndef NDEBUG
	/* if(BUILD IS DEBUG MODE) */
	const float DrawLineLength = 20;
	//DrawLine(head.x, head.y, head.x + vel.x * DrawLineLength, head.y + vel.y * DrawLineLength, MAGENTA); // Draw velocity
#endif
}

void EntitySprite::RenderShark() {
	/// Variables
	Vector2 vel = GetParent()->GetVel();

	float angleH = atan2(vel.y, vel.x);
	float angleL = angleH + 0.3 + PI / 2;
	float angleR = angleH - 0.3 - PI / 2;

	/* Calculate Triangle Points */
	Vector2 head = {
		20 * cos(angleH) + GetPos().x,
		20 * sin(angleH) + GetPos().y,
	};
	Vector2 tail = {
		50 * -cos(angleH) + GetPos().x,
		50 * -sin(angleH) + GetPos().y,
	};
	Vector2 left = {
		15 * cos(angleL) + GetPos().x,
		15 * sin(angleL) + GetPos().y,
	};
	Vector2 right = {
		15 * cos(angleR) + GetPos().x,
		15 * sin(angleR) + GetPos().y,
	};

	/* Draw the sharkies */
	DrawTriangle(head, right, GetPos(), Color{ 0, 121, 241, 100 });
	DrawTriangle(right, tail, GetPos(), Color{ 102, 191, 255, 100 });
	DrawTriangle(head, GetPos(), left, Color{ 80, 80, 80, 100 });
	DrawTriangle(left, GetPos(), tail, Color{ 130, 130, 130, 100 });

	DrawTriangleLines(head, right, GetPos(), BLUE);
	DrawTriangleLines(tail, right, GetPos(), SKYBLUE);
	DrawTriangleLines(head, GetPos(), left, DARKGRAY);
	DrawTriangleLines(tail, GetPos(), left, GRAY);
}

void EntitySprite::RenderWhale() {
	DrawRectangle(GetPos().x, GetPos().y, 200, 100, LIGHTGRAY);
}

#pragma endregion