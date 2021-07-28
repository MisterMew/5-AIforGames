#include "Agent.h"

/// VARIABLES
extern vector<EntityObject*> mEntity;
float MaxRandomVelocity = 5;
int MaxRandomAcceleration = 2;

/// AGENT CONSTRUCTORS
#pragma region [ Agent Constructors ]

Agent::Agent() : Agent({ 0, 0 }) {}

Agent::Agent(Vector2 pos) {
	EntityObject::SetPos(pos);
	SetVel({
		rand() % (int)MaxRandomVelocity - MaxRandomVelocity,
		rand() % (int)MaxRandomVelocity - MaxRandomVelocity
	});
	SetAcc({
		(float)(rand() % MaxRandomAcceleration + 1),
		(float)(rand() % MaxRandomAcceleration + 1)
	});

	mMaxSpeed = 3.5;
	mMaxForce = 0.5;
}

Agent::~Agent() {}

#pragma endregion

 /// UPDATE: AGENTS
/* Updates the AI for all agents */
void Agent::Update() {
	Vector2 vel = GetVel();
	Vector2 pos = GetPos();
	Vector2 acc = GetAcc();

	// Change velocity and position based on motion/acceleration
	vel.x += acc.x;
	vel.y += acc.y;
	SetVel(vel);
	SetAcc({ acc.x * 0.4f, acc.y * 0.4f }); //Slowly reduce acceleration

	pos.x += vel.x;
	pos.y += vel.y;

	// Entity Screen Wrap
	if (pos.x < 0) { pos.x = (float)GetScreenWidth(); }
	if (pos.y < 0) { pos.y = (float)GetScreenHeight(); }
	if (pos.x > (float)GetScreenWidth()) { pos.x = 0; }
	if (pos.y > (float)GetScreenHeight()) { pos.y = 0; }

	// Position
	SetPos(pos);

	// Boids
	for (auto enitity : mEntity) {
		Seperate(this);
		Cohese(this);
		Align(this);
	}
}

#pragma region [ Boid Rules ]

 /// BOID RULES: Seperation
/* Simulates the seperation of boid agents */
Vector2 Agent::Seperate(Agent* agent) {}

 /// BOID RULES: Alignment
/* Simulates the alignment of boid agents */
Vector2 Agent::Align(Agent* agent) {}

 /// BOID RULES: Cohesion
/* Simulates the cohesion of boid agents */
Vector2 Agent::Cohese(Agent* agent) {}

#pragma endregion

#pragma region [ Entity AI ]

 /// STEERING: SEEK
/* AI for an agent to Seek a target */
Vector2 Agent::Seek(const Vector2& v) {}

 /// STEERING: FLEE
/* AI for an agent to Flee a target */
void Agent::Flee() {}

 /// PATHFINDING: A*
/* AI to assist with pathfinding */
void Agent::Astar() {}

#pragma endregion



float Agent::Vector2Magnitude(Vector2 vec) {
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

Vector2 Agent::Vector2Clamp(Vector2 vec, float min, float max) {
	if (vec.x < min) { vec.x = min; }
	if (vec.y < min) { vec.y = min; }

	if (vec.x > max) { vec.x = max; }
	if (vec.y > max) { vec.y = max; }

	return vec;
}