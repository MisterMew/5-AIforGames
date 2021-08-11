#include "BehaviourAvoid.h"

Avoid::Avoid() {
	mTargetPosition = nullptr;

	mMaxSeeAhead = 100.0f;
	mMaxAvoidForce = 5.0f;

	mObstacles = nullptr;
}

Avoid::~Avoid() {}

void Avoid::Update(Agent& agent, float deltaTime) {
	// Get the distance between the target position and our position
	Vector2 distance = Vector2Subtract(*mTargetPosition, agent.GetPos());

	// Declare and set to 0 incase magnitude is 0
	Vector2 normal = Vector2Normalize(distance);

	// Calculate the force that will be added this frame
	Vector2 force = Vector2Subtract(Vector2Scale(normal, agent.GetMaxSpeed()), agent.GetVel());

	force = Vector2Scale(Vector2Normalize(force), agent.GetMaxForce());

	// set the force to the acceleration
	agent.GetAcc() = Vector2Add(force, agent.GetAcc());

	// If m_circles hasnt been set then there is no data to calculations on
	if (mObstacles == nullptr) {
		return;
	}

	// Get a normalized direction of the agent
	normal = Vector2Normalize(agent.GetVel());

	// Calculate how far to look ahead based on the agents velocity
	float dynamicSeeAhead = Vector2Length(agent.GetVel()) / agent.GetMaxSpeed();

	// Calculate the 2 positions to check at based on the dynamic see ahead value
	mAheadPosition = Vector2Add(agent.GetPos(), Vector2Scale(normal, dynamicSeeAhead));

	// Ditto: this one uses half of the dynamic see ahead value
	mAheadPosition2 = Vector2Add(agent.GetPos(), Vector2Scale(normal, dynamicSeeAhead * 0.5f));

	// The closest circle (obsticle)
	int mostThreateningIndex = -1;

	for (unsigned int i = 0; i < mObstacles->size(); i++)
	{
		// For both of the ahead positions: see if its distance from the agent is less than the circle radius		
		if (Vector2Length(Vector2Subtract((*mObstacles)[i]->mPosition, mAheadPosition)) <= (*mObstacles)[i]->mRadius ||
			Vector2Length(Vector2Subtract((*mObstacles)[i]->mPosition, mAheadPosition2)) <= (*mObstacles)[i]->mRadius)
		{
			// The distance between the agent and the current most threatening circle (closest)
			Vector2 thisToIndex{ 0,0 };
			if (mostThreateningIndex != -1)
			{
				thisToIndex = Vector2Subtract(agent.GetPos(), (*mObstacles)[mostThreateningIndex]->mPosition);
			}

			// The distance between the agent and the circle being checked in the current iteration
			Vector2 distanceAgent2Circle = Vector2Subtract(agent.GetPos(), (*mObstacles)[i]->mPosition);

			// if the distance of distanceAgent2Circle is less than the distance of the current closest circle || if the closest circle hasn't been set yet
			if (Vector2Length(distanceAgent2Circle) < Vector2Length(thisToIndex) || mostThreateningIndex == -1)
			{
				mostThreateningIndex = i;
			}
		}
	}

	// The force to apply to the agent to avoid the clostest obsticle
	Vector2 avoidanceForce = { 0,0 };

	// Check that there is a circle that we are going to collide with
	if (mostThreateningIndex != -1)
	{
		// The force is based off the distance between the agent and the closest circle
		avoidanceForce = Vector2Subtract(agent.GetPos(), (*mObstacles)[mostThreateningIndex]->mPosition);

		// Cap the force
		avoidanceForce = Vector2Scale(Vector2Normalize(avoidanceForce), mMaxAvoidForce);
	}

	// Apply the force to the agents acceleration
	agent.GetAcc() = Vector2Add(avoidanceForce, agent.GetAcc());
}