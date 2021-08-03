#include "Agent.h"

/// VARIABLES
extern vector<EntityObject*> mEntity;
float MaxRandomVelocity = 0;
int MaxRandomAcceleration = 0;

/// AGENT CONSTRUCTORS
#pragma region [ Agent Constructors ]

Agent::Agent() : Agent({ 0, 0 }) {}

Agent::Agent(Vector2 pos) {
	EntityObject::SetPos(pos);
	AllocateEntityParams();

	SetVel({
		rand() % (int)MaxRandomVelocity - MaxRandomVelocity, //Set the velocity's X value
		rand() % (int)MaxRandomVelocity - MaxRandomVelocity //Set the velocity's Y value
		});
	SetAcc({
		(float)(rand() % MaxRandomAcceleration + 1), //Set the acceleration's X value
		(float)(rand() % MaxRandomAcceleration + 1) //Set the acceleration's Y value
		});
	
}

Agent::~Agent() {}

#pragma endregion

/// UPDATE: AGENTS
/* Updates the AI for all agents */
void Agent::Update() {
	if (mAgentType == mFish) { Flock(); }

	Vector2 vel = GetVel();
	Vector2 pos = GetPos();
	Vector2 acc = GetAcc();

	// Change velocity and position based on motion/acceleration
	vel.x += acc.x;
	vel.y += acc.y;
	SetVel(Vector2Clamp(vel, -mMaxSpeed, mMaxSpeed));
	SetAcc({ 0, 0 });

	pos.x += vel.x;
	pos.y += vel.y;

	// Entity Screen Wrap
	if (pos.x < 0) { pos.x = (float)GetScreenWidth(); }
	if (pos.y < 0) { pos.y = (float)GetScreenHeight(); }
	if (pos.x > (float)GetScreenWidth()) { pos.x = 0; }
	if (pos.y > (float)GetScreenHeight()) { pos.y = 0; }

	// Position
	SetPos(pos);
}

   /// BOID RULES ///
#pragma region [ Boid Rules ]

 /// BOID RULES: Seperation
/* Simulates the seperation of boid agents */
Vector2 Agent::Seperate(Agent* agent) {
	Vector2 steer = { 0, 0 }; // GetSteerDirection();

	float count = 0;
	for (int i = 0; i < mEntity.size(); i++) { //for every boid in the list

		float distance = Vector2Distance(agent->GetPos(), mEntity[i]->GetPos()); //Calculate the distance between current boid and the other boid
		if (distance > 0.1f && distance < GetSeperation()) {					//If the boid is within range of the current boid,
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
		steer = Vector2Clamp(steer, -mMaxForce, mMaxForce);
		steer = Vector2Normalize(steer);
	}

	return steer;
}

/// BOID RULES: Alignment
/* Simulates the alignment of boid agents */
Vector2 Agent::Align(Agent* agent) {
	Vector2 ali = { 0, 0 };

	int count = 0;
	for (int i = 0; i < mEntity.size(); i++) {

		float distance = Vector2Distance(agent->GetPos(), mEntity[i]->GetPos());
		if (distance > 0 && distance < /* GetPerception() */ GetAlignment()) {
			ali = Vector2Add(ali, mEntity[i]->GetVel() /* ->GetPos() */);
			count++;
		}
	}

	if (count > 0) {
		ali = Vector2Divide(ali, (float)count); //Divide by the number of boids
		ali = Vector2Normalize(ali);		   //Normalise into unit vector
		ali = Vector2Scale(ali, mMaxSpeed);	  //Multiply by maxSpeed

		Vector2 steer = Vector2Subtract(ali, GetVel());
		steer = Vector2Clamp(steer, -mMaxForce, mMaxForce);

		return steer;
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
		if (distance > 0 && distance < GetCohesion()) {
			coh = Vector2Add(coh, mEntity[i]->GetPos());
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

#pragma region [ Entity AI ]

 /// BOID: Flocking
/* Execute Flocking behaviour */
void Agent::Flock() {
	// Boids
	Vector2 sep = Seperate(this);
	Vector2 coh = Cohese(this);
	Vector2 ali = Align(this);

	sep = Vector2Scale(sep, 0.75f);
	coh = Vector2Scale(coh, 0.5f);
	ali = Vector2Scale(ali, 0.8f);

	AddAcc(sep);
	AddAcc(ali);
	AddAcc(coh);
}

 /// STEERING: SEEK
/* AI for an agent to Seek a target */
Vector2 Agent::Seek(const Vector2& vector) {
	Vector2 seek = GetTargetSeek(); // GetTargetSeek();

	seek = Vector2Subtract(seek, vector); //Points to the desired target
	seek = Vector2Normalize(seek);
	seek = Vector2Scale(seek, mMaxSpeed);

	return Vector2Clamp(Vector2Subtract(seek, GetVel()), -mMaxForce, mMaxForce);
}

 /// STEERING: FLEE
/* AI for an agent to Flee a target */
bool Agent::Flee(Agent* agent) {
	Vector2 flee = Vector2Subtract(agent->GetPos(), mFleeTarget);

	float distance = Vector2Length(flee);
	if (distance > GetPerception()) {
		agent->AddForce({ -agent->GetVel().x, -agent->GetVel().y });
		return true;
	}

	if (distance == 0)	// on top of destination
		flee = { 1,0 };	// avoid errors when attempting to normalize a 0 vector

	Vector2 desiredVelocity = Vector2Scale(Vector2Normalize(flee), agent->GetMaxSpeed());
	Vector2 steeringForce = Vector2Subtract(desiredVelocity, agent->GetVel());

	agent->AddForce(steeringForce);

	return true;
}

 /// PATHFINDING: A*
/* AI to assist with pathfinding */
void Agent::Astar() {}

#pragma endregion

#pragma region [ Spawn Declarations ]

void Agent::AllocateEntityParams() {
	if (mAgentType == mFish) { //Allocate the parameters for Fish entities
		MaxRandomVelocity = 5;
		MaxRandomAcceleration = 2;

		mMaxSpeed = 2.0f;
		mMaxForce = 0.5f;

		SetPerception(20.0f);
		SetSeperation(17.5f);
		SetAlignment(20.0f);
		SetCohesion(17.5f);
	}
	if (mAgentType == mShark) { //Allocate the parameters for Shark entities
		MaxRandomVelocity = 7;
		MaxRandomAcceleration = 2;

		mMaxSpeed = 2.5f;
		mMaxForce = 0.7f;

		SetPerception(50.0f);
		SetSeperation(20.0f);
		SetAlignment(20.0f);
		SetCohesion(17.5f);
	}
	if (mAgentType == mWhale) { //Allocate the parameters for Whale entities
		MaxRandomVelocity = 0.5;
		MaxRandomAcceleration = 1;

		mMaxSpeed = 0.5;
		mMaxForce = 0.2;

		SetPerception(100);
		SetSeperation(30.0f);
		SetAlignment(20);
		SetCohesion(17.5f);
	}
}

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

Vector2 Agent::Truncate(Vector2 v, float max) {
	float i = max / Vector2Length(v);
	i = i < 1.0 ? i : 1.0;
	return Vector2Scale(v, i);
}
