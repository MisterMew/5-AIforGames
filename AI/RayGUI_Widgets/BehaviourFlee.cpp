#include "BehaviourFlee.h"
#include "raymath.h"
#include "Agent.h"

void Flee::Update(Agent* agent, float deltaTime) {
	Vector2 distance = Vector2Subtract(agent->GetPos(), GetTargetPos());						    // Get the distance between our position and the target position
	Vector2 normal = Vector2Normalize(distance);												   // Normalize the direction
	Vector2 force = Vector2Subtract(Vector2Scale(normal, agent->GetMaxSpeed()), agent->GetVel()); // Calculate the force that will be added this frame

	force = Vector2Scale(Vector2Normalize(force), agent->GetMaxForce());					    // Make sure its within the specified bounds
	agent->SetForce( Vector2Add(force, agent->GetForce()) );									   // Add the force to the acceleration
}