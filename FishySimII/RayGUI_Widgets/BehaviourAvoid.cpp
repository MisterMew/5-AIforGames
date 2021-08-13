#include "BehaviourAvoid.h"

AvoidBehaviour::AvoidBehaviour() { Init(); }
AvoidBehaviour::~AvoidBehaviour() {}


void AvoidBehaviour::Update(Agent& agent, float deltaTime) {
	Vector2 distance = Vector2Subtract(*mTargetPosition, agent.GetPos());						  // Get the distance between the target position and our position
	Vector2 normal = Vector2Normalize(distance);												 // Declare and set to 0 incase magnitude is 0
	Vector2 force = Vector2Subtract(Vector2Scale(normal, agent.GetMaxSpeed()), agent.GetVel()); // Calculate the force that will be added this frame

	force = Vector2Scale(Vector2Normalize(force), agent.GetMaxForce());
	
	agent.SetAcc(Vector2Add(force, agent.GetAcc())); // set the force to the acceleration

	if (mObstacles == nullptr) { return; }

	normal = Vector2Normalize(agent.GetVel()); // Get a normalized direction of the agent

	float dynamicSeeAhead = Vector2Length(agent.GetVel()) / agent.GetMaxSpeed();				  // Calculate how far to look ahead based on the agents velocity
	mAheadPosition = Vector2Add(agent.GetPos(), Vector2Scale(normal, dynamicSeeAhead));			 // Calculate the 2 positions to check at based on the dynamic see ahead value
	mAheadPosition2 = Vector2Add(agent.GetPos(), Vector2Scale(normal, dynamicSeeAhead * 0.5f)); // Ditto: this one uses half of the dynamic see ahead value

	// The closest circle (obsticle)
	int mostThreateningIndex = -1;

	for (unsigned int i = 0; i < mObstacles->size(); i++) {
		if (Vector2Length(Vector2Subtract((*mObstacles)[i]->mPosition, mAheadPosition)) <= (*mObstacles)[i]->mRadius || // For both of the ahead positions: see if its distance from the agent is less than the circle radius		
			Vector2Length(Vector2Subtract((*mObstacles)[i]->mPosition, mAheadPosition2)) <= (*mObstacles)[i]->mRadius) {
			
			Vector2 thisToIndex{ 0,0 }; // The distance between the agent and the current most threatening circle (closest)
			if (mostThreateningIndex != -1) {
				thisToIndex = Vector2Subtract(agent.GetPos(), (*mObstacles)[mostThreateningIndex]->mPosition);
			}

			Vector2 distanceAgent2Circle = Vector2Subtract(agent.GetPos(), (*mObstacles)[i]->mPosition); // The distance between the agent and the circle being checked in the current iteration
			
			if (Vector2Length(distanceAgent2Circle) < Vector2Length(thisToIndex) || mostThreateningIndex == -1) { // if the distance of distanceAgent2Circle is less than the distance of the current closest circle || if the closest circle hasn't been set yet
				mostThreateningIndex = i;
			}
		}
	}

	Vector2 avoidanceForce = { 0,0 }; // The force to apply to the agent to avoid the clostest obsticle

	if (mostThreateningIndex != -1) { // Check that there is a circle that we are going to collide with
		avoidanceForce = Vector2Subtract(agent.GetPos(), (*mObstacles)[mostThreateningIndex]->mPosition); // The force is based off the distance between the agent and the closest circle
		avoidanceForce = Vector2Scale(Vector2Normalize(avoidanceForce), mMaxAvoidForce); // Cap the force
	}

	agent.GetAcc() = Vector2Add(avoidanceForce, agent.GetAcc()); // Apply the force to the agents acceleration
	agent.SetVel(force);
}

void AvoidBehaviour::Init() {
	mTargetPosition = nullptr;

	mMaxSeeAhead = 100.0f;
	mMaxAvoidForce = 5.0f;

	mObstacles = nullptr;
}