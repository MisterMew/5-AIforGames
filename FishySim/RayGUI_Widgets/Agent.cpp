#include "Agent.h"

void Agent::Update() {
	Vector2 pos = GetPos();

	//Entity Screen Wrap
	if (pos.x < 0) { pos.x = GetScreenWidth(); }
	if (pos.y < 0) { pos.y = GetScreenHeight(); }
	if (pos.x > GetScreenWidth()) { pos.x = 0; }
	if (pos.y > GetScreenHeight()) { pos.y = 0; }

	// Position
	SetPos(pos);
	//Translate({(float)GetRandomValue(-5, 5), (float)GetRandomValue(-5, 5) });

	Vector2 facing = {GetPosG().m7, GetPosG().m8};
	Translate({ facing.x * GetVel().x, facing.y * GetVel().y });

	// Movement
	mVelocity.x += GetAcc().x;
	mVelocity.y += GetAcc().y;

	pos.x += GetVel().x;
	pos.y += GetVel().y;
}

#pragma region [ Boid Rules ]

 /// BOID RULES: Seperation
/* Simulates the seperation of boid agents */
void Agent::Seperate() {}

 /// BOID RULES: Alignment
/* Simulates the alignment of boid agents */
void Agent::Align() {}

 /// BOID RULES: Cohesion
/* Simulates the cohesion of boid agents */
void Agent::Cohese() {}

#pragma endregion

#pragma region [ Entity AI ]

/* AI for an agent to Seek a target */
void Agent::Seek() {}

/* AI for an agent to Flee a target */
void Agent::Flee() {}

#pragma endregion