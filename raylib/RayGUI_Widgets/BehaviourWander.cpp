#include "BehaviourWander.h"

Wander::Wander() { Init(); }
Wander::~Wander() {}

void Wander::Update(Agent& agent, float deltaTime) {
	mCurrentTimeStepping += deltaTime;

	// Check if its greater than the time stepping
	if (mCurrentTimeStepping >= mTimeStepping) {
		mCurrentTimeStepping = 0.0f;

		// get a random angle between - angleStepping and + angleStepping
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> distibution(-mAngleStepping * 2.0f, 0);
		float angleModifier = distibution(gen);

		agent.SetRotation(agent.GetRotation() + angleModifier);

		float s = sinf(agent.GetRotation());
		float c = cosf(agent.GetRotation());
		mTargetPosition.x = (agent.GetPos().x * c) - (agent.GetPos().y * s);
		mTargetPosition.y = (agent.GetPos().x * s) + (agent.GetPos().y * c);
	}

	Vector2 normal = Vector2Normalize(mTargetPosition);
	Vector2 force = Vector2Subtract(Vector2Scale(normal, agent.GetMaxSpeed()), agent.GetVel());

	force = Vector2Scale(force, agent.GetMaxForce());
	agent.GetAcc() = Vector2Add(force, agent.GetAcc()); 
}

void Wander::Init() {
	SetTargetPos(Vector2());
	SetAngleStepping(0.0F);
	SetTimeStepping(0.0F);
	SetCurrentTimeStepping(0.0F);
}