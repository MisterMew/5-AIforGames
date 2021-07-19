#include "simulation.h"

Entity::Entity() {}
//Entity::~Entity() {}

void Entity::UpdateEntity() {
	//Wrap Screen
	if (GetPos().x < 0) { mPosition.x = GetScreenWidth(); }
	if (GetPos().y < 0) { mPosition.y = GetScreenHeight(); }
	if (GetPos().x > GetScreenWidth()) { mPosition.x = 0; }
	if (GetPos().y > GetScreenHeight()) { mPosition.y = 0; }

	// Moves the entities
	SetAcc({GetAcc().x * 0.4f, GetAcc().y * 0.4f }); //Slows down slowing to be less abrupt

	mVelocity.x += GetAcc().x;
	mVelocity.y += GetAcc().y;

	mPosition.x += GetVel().x;
	mPosition.y += GetVel().y;

	SetAcc({ 0, 0 });
}

#pragma region [ Boid Rules ]

 /// BOID RULES: Seperation
/* Simulates the seperation of boid agents */
void Entity::Seperate() {}

/// BOID RULES: Alignment
/* Simulates the alignment of boid agents */
void Entity::Align() {}

/// BOID RULES: Cohesion
/* Simulates the cohesion of boid agents */
void Entity::Cohese() {}

#pragma endregion

#pragma region [ Entity AI ]

void Entity::Seek() {}

void Entity::Flee() {}

#pragma endregion

#pragma region [ Render Entity ]

 /// RENDER: Fish
/* Renders the fish entities */
void Entity::RenderFish() {
	float angleH = atan2(GetVel().y, GetVel().x);
	float angleL = angleH + 0.3 + PI / 2;
	float angleR = angleH - 0.3 - PI / 2;

	Vector2 head = {
		(mSize * 10) * cos(angleH) + GetPos().x,
		(mSize * 10) * sin(angleH) + GetPos().y,
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
	DrawTriangle(head, tailR, GetPos(), Color{255, 161, 0, 100});
	DrawTriangle(head, GetPos(), tailL, Color{190, 33, 55, 100});
	
	DrawTriangleLines(head, tailR, GetPos(), ORANGE);
	DrawTriangleLines(head, GetPos(), tailL, MAROON);
}

 /// RENDER: Shark
/* Renders the shark entities */
void Entity::RenderShark() {
	float angleH = atan2(GetVel().y, GetVel().x);
	Vector2 head = {
	10 * cos(angleH) + GetPos().x,
	10 * sin(angleH) + GetPos().y,
	};

	DrawRectangle(head.x, head.y, 50, 50, GRAY);
}

 /// RENDER: Whale
/* Renders the whale entities */
void Entity::RenderWhale() {}

#pragma endregion

float Distance(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}