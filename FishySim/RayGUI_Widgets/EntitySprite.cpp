#include "EntitySprite.h"

EntitySprite::EntitySprite(SpriteDrawType drawType) : mDrawType(drawType) {}
EntitySprite::~EntitySprite() {}

void EntitySprite::Start() {}
void EntitySprite::Update() {}

/* Render the fish sprite */
void EntitySprite::Draw() {
	if (!HasParent()) { return; }

	switch (mDrawType) {
	case SpriteDrawType::Fish:
		RenderFish();
		break;

	case SpriteDrawType::Shark:
		RenderFish();
		break;

	case SpriteDrawType::Whale:
		RenderFish();
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

void EntitySprite::RenderShark() {}

void EntitySprite::RenderWhale() {}

#pragma endregion