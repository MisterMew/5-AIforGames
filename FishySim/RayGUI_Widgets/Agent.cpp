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
	}
}

#pragma region [ Boid Rules ]

 /// BOID RULES: Seperation
/* Simulates the seperation of boid agents */
void Agent::Seperate(Agent* agent) {
	Vector2 steer = {0, 0};
	SetSeperation(20);

	int count = 0;
	for (int i = 0; i < mEntity.size(); i++) {
		float distance;

		if (sqrt(distance) != 0) {}
	}
}

 /// BOID RULES: Alignment
/* Simulates the alignment of boid agents */
void Agent::Align() {}

 /// BOID RULES: Cohesion
/* Simulates the cohesion of boid agents */
void Agent::Cohese() {}

#pragma endregion

#pragma region [ Entity AI ]

 /// STEERING: SEEK
/* AI for an agent to Seek a target */
void Agent::Seek() {}

 /// STEERING: FLEE
/* AI for an agent to Flee a target */
void Agent::Flee() {}

 /// PATHFINDING: A*
/* AI to assist with pathfinding */
void Agent::Astar() {}

#pragma endregion



float Vector2Magnitude(float x, float y) {
	return sqrt(x * x) + (y * y);
}