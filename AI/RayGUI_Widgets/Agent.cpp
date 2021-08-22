#include "Agent.h"

Agent::Agent() {}
Agent::~Agent() {}


#pragma region [ Public Functions ]

// Update the agent and its behaviours
void Agent::Update(float deltaTime) {
	Vector2 pos = GetPos();
	Vector2 vel = GetVel();

	SetForce({0, 0});

	/* UPDATE all behaviours */
	for (auto behaviour : mBehaviourList) {
		behaviour->Update(*this, deltaTime);
	}

	// If (velocity + steering) equals zero, then there is no movement
	SetVel( Truncate((Vector2Add(vel, Vector2Scale(GetForce(), deltaTime))), GetMaxSpeed()) );
	SetPos( (Vector2Add(pos, Vector2Scale(vel, deltaTime))) );

	SetVel( Vector2Scale(vel, GetFriction()) );
}

// Draw the agent
void Agent::Draw() {
	DrawPoly(GetPos(), 5, 10, 0, LIGHTGRAY);
}

/* Add a behaviour to the agent */
void Agent::AddBehaviour(Behaviour* behaviour) {
	mBehaviourList.push_back(behaviour);
}

#pragma endregion
#pragma region [ Private Functions ]

/* Truncate a vector with a float */
Vector2 Agent::Truncate(Vector2 v, float max) {
	float i = max / Vector2Length(v);
	i = i < 1.0 ? i : 1.0;

	return Vector2Scale(v, i);
}

#pragma endregion