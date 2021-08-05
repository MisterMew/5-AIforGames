#include "Agent.h"
#include "Behaviour.h"

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
	mForce = { 0,0 };

	for (int i = 0; i < mBehaviourList.size(); i++){
		mBehaviourList[i]->Update(this, deltaTime);
	}

	mVelocity = Truncate((Vector2Add(mVelocity, Vector2Scale(mForce, deltaTime))), mMaxSpeed);
	mPosition = (Vector2Add(mPosition, Vector2Scale(mVelocity, deltaTime)));

	mVelocity = Vector2Scale(mVelocity, mFriction);
}

// Draw the agent
void Agent::Draw() {
	DrawRectangle(mPosition.x, mPosition.y, 10, 10, RED);
}

// Add a behaviour to the agent
void Agent::AddBehaviour(Behaviour* behaviour) {
	mBehaviourList.push_back(behaviour);
}