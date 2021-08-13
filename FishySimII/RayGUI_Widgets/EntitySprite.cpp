#include "EntitySprite.h"

EntitySprite::EntitySprite() {}
EntitySprite::EntitySprite(EntityType entityType) : mEntityType(entityType) {}
EntitySprite::~EntitySprite() {}

void EntitySprite::Start() {}
void EntitySprite::Update(float deltaTime) {}

/* Choose which sprite to render */
void EntitySprite::Draw() {
	if (!HasParent()) { return; }

	switch (mEntityType) {
	case EntityType::objFish:
		RenderFish();
		break;

	case EntityType::objShark:
		RenderShark();
		break;

	case EntityType::objWhale:
		RenderWhale();
		break;

	case EntityType::objBubble:
		RenderBubble();
		break;

	default: break;
	}
}

#pragma region [ Sprite Rendering ]

 /// RENDER: FISH
/* Renders the sprite for the FISH */
void EntitySprite::RenderFish() {
	GetDrawPoints(10, NULL, 6, 6);
	
#ifndef NDEBUG
	DrawCircleLines(GetPos().x, GetPos().y, 75, BLACK);
#endif

	/* Draw the fishies */
	DrawTriangle(head, right, GetPos(), Color{ 255, 161, 0, 100 });
	DrawTriangle(head, GetPos(), left, Color{ 190, 33, 55, 100 });

	DrawTriangleLines(head, right, GetPos(), ORANGE);
	DrawTriangleLines(head, GetPos(), left, MAROON);

}

 /// RENDER: SHARK
/* Renders the sprite for the SHARK */
void EntitySprite::RenderShark() {}

 /// RENDER: WHALE
/* Renders the sprite for the WHALE */
void EntitySprite::RenderWhale() {}

void EntitySprite::RenderBubble() {
	DrawCircle(GetPos().x, GetPos().y, 10, Color{ 23, 23, 23, 200 });
}
#pragma endregion

#pragma region [ Drawing Calculations ]

/* Get the points needed to dynamically draw thhe sprites using raylib shapes */
Vector2 EntitySprite::GetDrawPoints(float h, float t, float L, float R) {
	Vector2 vel = GetParent()->GetVel();

	float angleH = atan2(vel.y, vel.x); //Calculates the rotation
	float angleL = angleH + 0.3 + PI / 2;
	float angleR = angleH - 0.3 - PI / 2;

	/* Calculate Triangle Points */
	head = {
		h * cos(angleH) + GetPos().x,
		h * sin(angleH) + GetPos().y,
	};
	tail = {
		t * -cos(angleH) + GetPos().x,
		t * -sin(angleH) + GetPos().y,
	};
	left = {
		L * cos(angleL) + GetPos().x,
		L * sin(angleL) + GetPos().y,
	};
	right = {
		R * cos(angleR) + GetPos().x,
		R * sin(angleR) + GetPos().y,
	};

	return head, tail, left, right;
}

#pragma endregion