#include "BehaviourWander.h"
#include "raymath.h"
#include "Agent.h"

Wander::Wander() {
	SetTargetPos( Vector2() );
	SetAngleTimeStep( 0.0F );
	SetTimeStep( 0.0F );
	SetCurTimeStep( 0.0F );
}

void Wander::Update(Agent* agent, float deltaTime) {
	if (GetCurTimeStep() >= GetTimeStep()) { // Check if its greater than the time stepping
		SetCurTimeStep( 0.0f );				//Reset time

		// get a random angle between - angleStepping and + angleStepping
		std::random_device rdm;
		std::mt19937 gen(rdm());
		std::uniform_real_distribution<float> distribution(-GetAngleStep() * 2.0F, 0);
		float angleModifier = distribution(gen);

		SetTargetPos({
			(agent->GetPos().x - agent->GetPos().y),
			(agent->GetPos().x + agent->GetPos().y)
		});
	}

	Vector2 normal = Vector2Normalize(GetTargetPos());											   //Get the normal of the new target position
	Vector2 force = Vector2Subtract(Vector2Scale(normal, agent->GetMaxSpeed()), agent->GetVel()); //Calculate the force to get there
	force = Vector2Scale(force, agent->GetMaxForce());										     //Cap the force
	
	agent->SetAcc( Vector2Add(force, agent->GetAcc()) ); //Apply the force to acceleration
}
