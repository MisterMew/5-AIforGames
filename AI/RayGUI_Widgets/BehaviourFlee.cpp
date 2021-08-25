#include "BehaviourFlee.h"

FleeBehaviour::FleeBehaviour() {}
FleeBehaviour::~FleeBehaviour() {}

/// BEHAVIOUR: Seek
/* A combination of the two seek behaviours from AIE Samples [AI_Flocking] & [AI_Seek] */
void FleeBehaviour::Update(Agent& agent, float deltaTime) {
	if (mTargetPosition == nullptr) { return; }

	Vector2 pos = agent.GetPos();
	Vector2 vel = agent.GetVel();
	Vector2 acc = agent.GetAcc();

	agent.SetForce({ 0, 0 });

	Vector2 distance = Vector2Subtract(*mTargetPosition, agent.GetPos()); // Get the distance between the target position and our position
	if (distance.x == 0 && distance.y == 0) {
		return;
	}

	vel = Vector2Subtract(vel, Vector2Normalize(distance)); // Normalise the direction

	vel.x += acc.x * deltaTime;  // * deltaTime to smooth no matter framerate
	vel.y += acc.y * deltaTime; // * deltaTime to smooth no matter framerate
	agent.SetVel(Agent::Vector2Clamp(vel, -agent.GetMaxSpeed(), agent.GetMaxSpeed()));
	agent.SetAcc({ 0, 0 });

	pos.x += vel.x;
	pos.y += vel.y;

	agent.WrapScreenBounds(&pos); // Changed this to reference 'pos', so that it modifies the value
	agent.SetPos(pos);
}