#include "BehaviourSeek.h"


Seek::Seek() {
	mTargetPosition = nullptr;
}

Seek::~Seek() {}

void Seek::Update(Agent& agent, float deltaTime) {
	if (mTargetPosition != nullptr) {
		Vector2 distance = Vector2Subtract(*mTargetPosition, agent.GetPos()); // Get the distance between the target position and our position

		if (Vector2Length(distance) > 0) {
			Vector2 normal = Vector2Normalize(distance); // Normalize the direction
			Vector2 force = Vector2Subtract(Vector2Scale(normal, agent.GetMaxSpeed()), agent.GetVel()); // Calculate the force that will be added this frame

			force = Vector2Scale(Vector2Normalize(force), agent.GetMaxForce()); // Make sure its within the specified bounds

			agent.GetAcc() = Vector2Add(force, agent.GetAcc()); // Add the force to the acceleration
		}
	}
}
