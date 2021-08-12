#include "BehaviourFlock.h"

FlockBehaviour::FlockBehaviour() {}
FlockBehaviour::~FlockBehaviour() {}

extern vector<EntityObject*> entities; //entities is defined in main.cpp

 /// BOID FLOCKING
/* Enables complete flocking */
void FlockBehaviour::Flock(Agent* agent, float sepCoef, float aliCoef, float cohCoef) {
	Vector2 sep = Seperate(agent);
	Vector2 coh = Cohese(agent);
	Vector2 ali = Align(agent);

	sep = Vector2Scale(sep, sepCoef);
	ali = Vector2Scale(ali, aliCoef);
	coh = Vector2Scale(coh, cohCoef);

	agent->AddAcc(sep);
	agent->AddAcc(ali);
	agent->AddAcc(coh);
}

#pragma region [ Boid Rules ]

 /// BOID RULES: Seperation
/* Simulates the seperation of boid agents */
Vector2 FlockBehaviour::Seperate(Agent* agent) {
	Vector2 steer = { 0, 0 }; // GetSteerDirection();

	float count = 0;
	for (int i = 0; i < entities.size(); i++) { //for every boid in the list

		float distance = Vector2Distance(agent->GetPos(), entities[i]->GetPos()); //Calculate the distance between current boid and the other boid
		if (distance > 0.1f && distance < GetSeperation()) {					//If the boid is within range of the current boid,
			Vector2 direction = { 0, 0 };									   //Seperate the boids:
			direction = Vector2Subtract(agent->GetPos(), entities[i]->GetPos());
			direction = Vector2Normalize(direction);
			direction = Vector2Divide(direction, distance);

			steer = Vector2Add(steer, direction);
			count++;
		}
	}

	if (count > 0) {
		steer = Vector2Divide(steer, (float)count);
	}

	if (Agent::Vector2Magnitude(steer) > 0) { // Steering = SepValue - Velocity
		steer = Vector2Normalize(steer);
		steer = Vector2Scale(steer, agent->GetMaxSpeed());
		steer = Vector2Subtract(steer, agent->GetVel());
		steer = Agent::Vector2Clamp(steer, -agent->GetMaxForce(), agent->GetMaxForce());
		steer = Vector2Normalize(steer);
	}

	return steer;
}

 /// BOID RULES: Alignment
/* Simulates the alignment of boid agents */
Vector2 FlockBehaviour::Align(Agent* agent) {
	Vector2 ali = { 0, 0 };

	int count = 0;
	for (int i = 0; i < entities.size(); i++) {

		float distance = Vector2Distance(agent->GetPos(), entities[i]->GetPos());
		if (distance > 0 && distance < /* GetPerception() */ GetAlignment()) {
			ali = Vector2Add(ali, entities[i]->GetVel() /* ->GetPos() */);
			count++;
		}
	}

	if (count > 0) {
		ali = Vector2Divide(ali, (float)count); //Divide by the number of boids
		ali = Vector2Normalize(ali);		   //Normalise into unit vector
		ali = Vector2Scale(ali, agent->GetMaxSpeed());	  //Multiply by maxSpeed

		Vector2 steer = Vector2Subtract(ali, agent->GetVel());
		steer = Agent::Vector2Clamp(steer, -agent->GetMaxForce(), agent->GetMaxForce());

		return steer;
	}
	else { return { 0, 0 }; }
}

 /// BOID RULES: Cohesion
/* Simulates the cohesion of boid agents */
Vector2 FlockBehaviour::Cohese(Agent* agent) {
	Vector2 coh = { 0, 0 };

	int count = 0;
	for (int i = 0; i < entities.size(); i++) {

		float distance = Vector2Distance(agent->GetPos(), entities[i]->GetPos());
		if (distance > 0 && distance < GetCohesion()) {
			coh = Vector2Add(coh, entities[i]->GetPos());
			count++;
		}
	}

	if (count > 0) {
		coh = Vector2Divide(coh, (float)count);
		coh = Vector2Subtract(coh, agent->GetPos());
		coh = Vector2Normalize(coh);
		return coh;
	}
	else { return { 0, 0 }; }
}

#pragma endregion