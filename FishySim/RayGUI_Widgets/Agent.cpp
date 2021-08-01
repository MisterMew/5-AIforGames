#include "Agent.h"

/// VARIABLES
extern vector<EntityObject*> mEntity;
float MaxRandomVelocity = 5;
int MaxRandomAcceleration = 2;

/// AGENT CONSTRUCTORS
#pragma region [ Agent Constructors ]

Agent::Agent() : Agent({ 0, 0 }) {}

Agent::Agent(Vector2 pos) {
	EntityObject::SetPos(pos);
	SetVel({
		rand() % (int)MaxRandomVelocity - MaxRandomVelocity,
		rand() % (int)MaxRandomVelocity - MaxRandomVelocity
	});
	SetAcc({
		(float)(rand() % MaxRandomAcceleration + 1),
		(float)(rand() % MaxRandomAcceleration + 1)
	});

	mMaxSpeed = 3.5;
	mMaxForce = 0.5;

	SetPerception(20);
	SetSeperation(0.5f);
	SetAlignment(10);
	SetCohesion(20);
}

Agent::~Agent() {}

#pragma endregion

/// UPDATE: AGENTS
/* Updates the AI for all agents */
void Agent::Update() {
	Vector2 vel = GetVel();
	Vector2 pos = GetPos();
	Vector2 acc = GetAcc();

	// Change velocity and position based on motion/acceleration
	vel.x += acc.x;
	vel.y += acc.y;
	SetVel(vel);
	SetAcc({ acc.x * 0.4f, acc.y * 0.4f }); //Slowly reduce acceleration

	pos.x += vel.x;
	pos.y += vel.y;

	// Entity Screen Wrap
	if (pos.x < 0) { pos.x = (float)GetScreenWidth(); }
	if (pos.y < 0) { pos.y = (float)GetScreenHeight(); }
	if (pos.x > (float)GetScreenWidth()) { pos.x = 0; }
	if (pos.y > (float)GetScreenHeight()) { pos.y = 0; }

	// Boids
	for (auto enitity : mEntity) {
		Vector2 sep = Seperate(this);
		Vector2 coh = Cohese(this);
		Vector2 ali = Align(this);

		sep = Vector2Scale(sep, 1.5);
		coh = Vector2Scale(coh, 1.5);
		ali = Vector2Scale(ali, 1.5);

		SetAcc(Vector2Add(GetAcc(), sep));
		SetAcc(Vector2Add(GetAcc(), coh));
		SetAcc(Vector2Add(GetAcc(), ali));
	}

	// Position
	SetPos(pos);
}

#pragma region [ Boid Rules ]
/// BOID RULES: Seperation
/* Simulates the seperation of boid agents */
Vector2 Agent::Seperate(Agent* agent) {
	SetSteering({ 0, 0 });
	Vector2 steer = GetSteerDirection();

	float count = 0;
	for (int i = 0; i < mEntity.size(); i++) { //for every boid in the list

		float distance = Vector2Distance(agent->GetPos(), mEntity[i]->GetPos()); //Calculate the distance between current boid and the other boid
		if (distance > 0 && distance < GetSeperation()) {						//If the boid is within range of the current boid,
			Vector2 direction = { 0, 0 };									   //Seperate the boids:
			direction = Vector2Subtract(agent->GetPos(), mEntity[i]->GetPos());
			direction = Vector2Normalize(direction);
			direction = Vector2Divide(direction, distance);

			steer = Vector2Add(steer, direction);
			count++;
		}
	}

	if (count > 0) {
		steer = Vector2Divide(steer, (float)count);
	}

	if (Vector2Magnitude(steer) > 0) { // Steering = SepValue - Velocity
		steer = Vector2Normalize(steer);
		steer = Vector2Scale(steer, mMaxSpeed);
		steer = Vector2Subtract(steer, GetVel());
		steer = Vector2Clamp(steer, 0, mMaxForce);
	}
	
	SetSteering(steer);
	return GetSteerDirection();
}

/// BOID RULES: Alignment
/* Simulates the alignment of boid agents */
Vector2 Agent::Align(Agent* agent) {
	Vector2 ali = { 0, 0 };

	int count = 0;
	for (int i = 0; i < mEntity.size(); i++) {

		float distance = Vector2Distance(agent->GetPos(), mEntity[i]->GetPos());
		if (distance > 0 && distance < GetPerception()) {
			ali = Vector2Add(ali, mEntity[i]->GetPos());
			count++;
		}
	}

	if (count > 0) {
		ali = Vector2Divide(ali, (float)count); //Divide by the number of boids
		ali = Vector2Normalize(ali);		   //Normalise into unit vector
		ali = Vector2Scale(ali, mMaxSpeed);	  //Multiply by maxSpeed

		SetSteering((Vector2Subtract(ali, GetVel())));
		Vector2Clamp(GetSteerDirection(), 0, mMaxForce);

		return GetSteerDirection();
	}
	else { return { 0, 0 }; }
}

/// BOID RULES: Cohesion
/* Simulates the cohesion of boid agents */
Vector2 Agent::Cohese(Agent* agent) {
	Vector2 coh = { 0, 0 };

	int count = 0;
	for (int i = 0; i < mEntity.size(); i++) {

		float distance = Vector2Distance(agent->GetPos(), mEntity[i]->GetPos());
		if (distance > 0 && distance < GetPerception()) {
			coh = Vector2Add(coh, mEntity[i]->GetPos());
			count++;
		}
	}

	if (count > 0) {
		coh = Vector2Divide(coh, (float)count);
		return Seek(coh);
	}
	else { return { 0, 0 }; }
}

#pragma endregion

#pragma region [ Entity AI ]

/// STEERING: SEEK
/* AI for an agent to Seek a target */
Vector2 Agent::Seek(const Vector2& v) {
	Vector2 seek = GetTargetSeek();

	seek = Vector2Subtract(seek, v); //Points to the desired target
	Vector2Normalize(seek);
	Vector2Scale(seek, mMaxSpeed);

	SetAcc((Vector2Subtract(seek, GetVel())));
	SetAcc((Vector2Clamp(GetAcc(), 0, mMaxForce)));

	return GetAcc();
}

/// STEERING: FLEE
/* AI for an agent to Flee a target */
void Agent::Flee() {}

/// PATHFINDING: A*
/* AI to assist with pathfinding */
void Agent::Astar() {}

#pragma endregion


/// MATH STUFF
float Agent::Vector2Magnitude(Vector2 vec) {
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

Vector2 Agent::Vector2Clamp(Vector2 vec, float min, float max) {
	if (vec.x < min) { vec.x = min; }
	if (vec.y < min) { vec.y = min; }

	if (vec.x > max) { vec.x = max; }
	if (vec.y > max) { vec.y = max; }

	return vec;
}