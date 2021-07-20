#include "Agent.h"

float MaxRandomVelocity = 5;
int MaxRandomAcceleration = 2;

Agent::Agent() {}

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

void Agent::Update() {
	Vector2 vel = GetVel();
	Vector2 pos = GetPos();
	Vector2 acc = GetAcc();

	// Change velocity and position based on motion/acceleration

	vel.x += acc.x;
	vel.y += acc.y;
	SetVel(vel);
	SetAcc({ acc.x * 0.4f, acc.y * 0.4f }); // Slowly reduce acceleration

	pos.x += vel.x;
	pos.y += vel.y;

	// Entity Screen Wrap
	if (pos.x < 0) { pos.x = GetScreenWidth(); }
	if (pos.y < 0) { pos.y = GetScreenHeight(); }
	if (pos.x > GetScreenWidth()) { pos.x = 0; }
	if (pos.y > GetScreenHeight()) { pos.y = 0; }

	// Position
	SetPos(pos);
}

#pragma region [ Boid Rules ]

 /// BOID RULES: Seperation
/* Simulates the seperation of boid agents */
Vector2 Agent::Seperate(Agent* agent) {
	mPerceptionRadius = 50;
	Vector2 steering = Vector2();

	float total = 0;
	for (int i = 0; i < sizeof(agent); i++) {
		float dist = 0;
		if (InPerception(agent[i], GetPerception(), 0)) {
			Vector2 difference = Vector2Subtract(difference, agent[i].GetPos());
			if (dist * dist != 0)
				difference = Vector2Divide(difference, dist * dist);
			steering = Vector2Add(steering, difference);
			total++;
		}
	}
	if (total > 0)
	{
		steering = Vector2Divide(steering, total);
		steering = Vector2MultiplyV(steering, mMaxSpeed);
		steering = Vector2Subtract(steering, GetVel());
		steering = Clamp(steering, -mMaxForce, mMaxForce);
	}
	return steering;
}

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

bool Agent::InPerception(Agent* target, float radius, float distance) {
	if (this == target) {
		distance = 0;
		return false;
	}

	// calculate distance between both boids.
	distance = Vector2Distance(this.GetPos(), target.GetPos());
	if (distance > radius)
		return false;

	return true;
}