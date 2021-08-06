#include "Agent.h"

Agent::Agent() {}
Agent::Agent(Vector2 pos) { SetPos(pos); }
Agent::~Agent() {}

Vector2 Agent::Truncate(Vector2 v, float max) {
	float i = max / Vector2Length(v);
	i = i < 1.0 ? i : 1.0;
	return Vector2Scale(v, i);
}

// Update the agent and its behaviours
void Agent::Update(float deltaTime) {
	SetForce({0, 0});

	Vector2 pos = GetPos();
	Vector2 vel = GetVel();
	Vector2 acc = GetAcc();
	Vector2 force = GetForce();

	// Change velocity and position based on motion/acceleration
	vel.x += acc.x;
	vel.y += acc.y;
	SetVel(Vector2Clamp(vel, -mMaxSpeed, mMaxSpeed));
	SetAcc({ 0, 0 });

	pos.x += vel.x;
	pos.y += vel.y;

	// Entity Screen Wrap
	if (pos.x < 0) { pos.x = (float)GetScreenWidth(); }
	if (pos.y < 0) { pos.y = (float)GetScreenHeight(); }
	if (pos.x > (float)GetScreenWidth()) { pos.x = 0; }
	if (pos.y > (float)GetScreenHeight()) { pos.y = 0; }

	// Position
	SetPos(pos);

	for (int i = 0; i < mBehaviourList.size(); i++){
		mBehaviourList[i]->Update(this, deltaTime);
	}

	SetVel(Truncate((Vector2Add(vel, Vector2Scale(force, deltaTime))), GetMaxSpeed()));
	SetPos((Vector2Add(pos, Vector2Scale(vel, deltaTime))));

	SetVel(Vector2Scale(vel, GetFriction()));
}

// Add a behaviour to the agent
void Agent::AddBehaviour(Behaviour* behaviour) {
	mBehaviourList.push_back(behaviour);
}




Vector2 Agent::Truncate(Vector2 v, float max) {
	float i = max / Vector2Length(v);
	i = i < 1.0 ? i : 1.0;
	return Vector2Scale(v, i);
}

Vector2 Agent::Vector2Clamp(Vector2 vec, float min, float max) {
	if (vec.x < min) { vec.x = min; }
	if (vec.y < min) { vec.y = min; }

	if (vec.x > max) { vec.x = max; }
	if (vec.y > max) { vec.y = max; }

	return vec;
}

float Agent::Vector2Magnitude(Vector2 vec) {
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}