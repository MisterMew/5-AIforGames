#include "Agent.h"

Agent::Agent() {}

Agent::Agent(Vector2 pos) {
	/*EntityObject::SetPos(pos);
	SetVel({(float)(rand()%5 - 2), (float)(rand()%5 - 2)});
	SetAcc({2, 2});
	*/
}

Agent::~Agent() {}

void Agent::Update() {
	Vector2 vel = GetVel();
	Vector2 pos = GetPos();

	//Entity Screen Wrap
	if (pos.x < 0) { pos.x = GetScreenWidth(); }
	if (pos.y < 0) { pos.y = GetScreenHeight(); }
	if (pos.x > GetScreenWidth()) { pos.x = 0; }
	if (pos.y > GetScreenHeight()) { pos.y = 0; }

	// Position
	SetPos(pos);
	Translate({(float)GetRandomValue(5, 0), (float)GetRandomValue(0, 5) });

	vel.x += GetAcc().x;
	vel.y += GetAcc().y;

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