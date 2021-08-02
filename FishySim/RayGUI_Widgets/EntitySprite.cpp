#include "EntitySprite.h"

EntitySprite::EntitySprite(SpriteDrawType drawType) : mDrawType(drawType) {}
EntitySprite::~EntitySprite() {}

void EntitySprite::Start() {}
void EntitySprite::Update() {}

/* Choose which sprite to render */
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
 /// RENDER: FISH
/* Renders the sprite for the FISH */
void EntitySprite::RenderFish() {
	GetDrawPoints(10, NULL, 6, 6);
	
	/* Draw the fishies */
	DrawTriangle(head, right, GetPos(), Color{ 255, 161, 0, 100 });
	DrawTriangle(head, GetPos(), left, Color{ 190, 33, 55, 100 });

	DrawTriangleLines(head, right, GetPos(), ORANGE);
	DrawTriangleLines(head, GetPos(), left, MAROON);
}

 /// RENDER: SHARK
/* Renders the sprite for the SHARK */
void EntitySprite::RenderShark() {
	GetDrawPoints(20, 50, 15, 15);

	/* Draw the sharkies */
	DrawTriangle(head, right, GetPos(), Color{0, 121, 241, 100});
	DrawTriangle(right, tail, GetPos(), Color{102, 191, 255, 100});
	DrawTriangle(head, GetPos(), left, Color{80, 80, 80, 100});
	DrawTriangle(left, GetPos(), tail, Color{130, 130, 130, 100});

	DrawTriangleLines(head, right, GetPos(), BLUE);
	DrawTriangleLines(tail, right, GetPos(), SKYBLUE);
	DrawTriangleLines(head, GetPos(), left, DARKGRAY);
	DrawTriangleLines(tail, GetPos(), left, GRAY);
}

 /// RENDER: WHALE
/* Renders the sprite for the WHALE */
void EntitySprite::RenderWhale() {
	GetDrawPoints(50, 170, 40, 40);

	float whaleHead = 120;
	Vector2 vel = GetParent()->GetVel();
	Vector2 temp = Vector2Subtract(left, right);
	float distance = Vector2Mag(temp);

	/* Draw the whalies */
	DrawRectanglePro({ right.x, right.y, whaleHead, distance }, { 0,0 }, (atan2(vel.y, vel.x) * RAD2DEG), Color{255, 255, 255, 150});
	DrawRectangleLinesPro({ right.x, right.y, whaleHead, distance }, { 0,0 }, (atan2(vel.y, vel.x) * RAD2DEG), RAYWHITE);
	
	DrawTriangle(head, right, GetPos(), Color{200, 200, 200, 100});     //top-left
	DrawTriangle(right, tail, GetPos(), Color{255, 255, 255, 100}); //bot-left
	DrawTriangle(head, GetPos(), left, Color{80, 80, 80, 100});  //top-right
	DrawTriangle(left, GetPos(), tail, Color{130, 130, 130, 100});//bot-right

	DrawTriangleLines(head, right, GetPos(), LIGHTGRAY);
	DrawTriangleLines(tail, right, GetPos(), WHITE);
	DrawTriangleLines(head, GetPos(), left, DARKGRAY);
	DrawTriangleLines(tail, GetPos(), left, GRAY);

	DrawTriangle(left, GetPos(), right, Color{135, 60, 190, 50}); //Back
	DrawTriangleLines(left, GetPos(), right, VIOLET);
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

#ifndef NDEBUG
	/// DEBUG MODE
   /* if(BUILD IS DEBUG MODE) */
	const float DrawLineLength = 20;
	DrawLine(head.x, head.y, head.x + vel.x * DrawLineLength, head.y + vel.y * DrawLineLength, DARKGRAY); // Draw velocity
#endif

	return head, tail, left, right;
}

/* Modified version of DrawRectanglePro to draw lines */
void EntitySprite::DrawRectangleLinesPro(Rectangle rec, Vector2 origin, float rotation, Color color) {
	Vector2 topLeft = { 0 };
	Vector2 topRight = { 0 };
	Vector2 bottomLeft = { 0 };
	Vector2 bottomRight = { 0 };

	// Only calculate rotation if needed
	if (rotation == 0.0f) {
		float x = rec.x - origin.x;
		float y = rec.y - origin.y;

		topLeft = Vector2{ x, y };
		topRight = Vector2{ x + rec.width, y };
		bottomLeft = Vector2{ x, y + rec.height };
		bottomRight = Vector2{ x + rec.width, y + rec.height };
	}
	else {
		float sinRotation = sinf(rotation * DEG2RAD);
		float cosRotation = cosf(rotation * DEG2RAD);
		float x = rec.x;
		float y = rec.y;
		float dx = -origin.x;
		float dy = -origin.y;

		topLeft.x = x + dx * cosRotation - dy * sinRotation;
		topLeft.y = y + dx * sinRotation + dy * cosRotation;

		topRight.x = x + (dx + rec.width) * cosRotation - dy * sinRotation;
		topRight.y = y + (dx + rec.width) * sinRotation + dy * cosRotation;

		bottomLeft.x = x + dx * cosRotation - (dy + rec.height) * sinRotation;
		bottomLeft.y = y + dx * sinRotation + (dy + rec.height) * cosRotation;

		bottomRight.x = x + (dx + rec.width) * cosRotation - (dy + rec.height) * sinRotation;
		bottomRight.y = y + (dx + rec.width) * sinRotation + (dy + rec.height) * cosRotation;
	}

	DrawLine(topLeft.x, topLeft.y, topRight.x, topRight.y, color);
	DrawLine(topRight.x, topRight.y, bottomRight.x, bottomRight.y, color);
	DrawLine(bottomRight.x, bottomRight.y, bottomLeft.x, bottomLeft.y, color);
	//DrawLine(bottomLeft.x, bottomLeft.y, topLeft.x, topLeft.y, color);
}

/* Calculates the Magnitude of a Vector2 */
float EntitySprite::Vector2Mag(Vector2 vec) {
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

#pragma endregion