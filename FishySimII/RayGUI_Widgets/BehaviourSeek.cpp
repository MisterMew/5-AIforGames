#include "BehaviourSeek.h"

SeekBehaviour::SeekBehaviour() {}
SeekBehaviour::~SeekBehaviour() {}

 /// BEHAVIOUR: Seek
/* A combination of the two seek behaviours from AIE Samples [AI_Flocking] & [AI_Seek] */
void SeekBehaviour::Update(Agent& agent, float deltaTime) {
	if (mTargetPosition == nullptr) { return; }
	
	Vector2 distance = Vector2Subtract(*mTargetPosition, agent.GetPos()); // Get the distance between the target position and our position
	if (distance.x == 0 && distance.y == 0) {
		return;
	}

	Vector2 normal = Vector2Normalize(distance); // Normalise the direction
	Vector2 steeringForce = agent.GetForce();			// Get the agents force

			steeringForce = Vector2Subtract(Vector2Scale(normal, agent.GetMaxSpeed()), agent.GetVel()); // Calculate the force that will be added this frame
			steeringForce = Vector2Scale(Vector2Normalize(steeringForce), agent.GetMaxForce()); // Make sure its within the specified bounds

	agent.SetAcc(Vector2Add(steeringForce, agent.GetAcc())); // Add the force to the acceleration

	agent.SetForce(steeringForce);
	agent.AddForce(steeringForce);
}