#pragma once
#include "EntityObject.h"

class Agent : public EntityObject {
	 /// Variables
	/* Boid Variables */
	bool mIsPredator;

<<<<<<< HEAD
	Vector2 mSteeringDirection;
	float mPerceptionRadius;
	float mMaxSpeed;
	float mMaxForce;


	/* Boid Variables */
=======
>>>>>>> parent of ebb9e7f (fixed~)
	float mSeperation;
	float mAlignment;
	float mCohesion;

	Vector2 mSeekTarget;
	Vector2 mFleeTarget;

public: 
	//AgentType mAgentType;

	 /// Function Declarations
	Agent();
	Agent(Vector2 pos);
	~Agent();

	void Update() override;

	/* Boid Law Functions */
<<<<<<< HEAD
	void Flock(float sepCoef, float aliCoef, float cohCoef);
	Vector2 Seperate(Agent* agent);
	Vector2 Align(Agent* agent);
	Vector2 Cohese(Agent* agent);

	Vector2 Seek(const Vector2& v);
	bool Flee(Agent* agent);
	void Astar();

	/* Create Entities */
	void CheckAgentType();
	void AllocateEntityParams(float maxVel, int maxAcc, float maxSpd, float maxForce, float perception, float sep, float ali, float coh);
=======
	void Seperate();
	void Align();
	void Cohese();
>>>>>>> parent of ebb9e7f (fixed~)

	/* Math Assists */
	float Vector2Magnitude(Vector2 vec);
	Vector2 Vector2Clamp(Vector2 vec, float min, float max);
	Vector2 Truncate(Vector2 v, float max);


	 /// Function Definitions
<<<<<<< HEAD
	bool IsPredator() { return mIsPredator; }

	Vector2 GetSteerDirection() { return mSteeringDirection; }
	float GetPerception() { return mPerceptionRadius; }
	float GetMaxSpeed() { return mMaxSpeed; }
	float GetMaxForce() { return mMaxForce; }

	void SetSteering(Vector2 steer) { mSteeringDirection = steer; }
	void SetPerception(float p) { mPerceptionRadius = p; }
	void SetMaxSpeed(float maxSpd) { mMaxSpeed = maxSpd; }
	void SetMaxForce(float maxFrc) { mMaxSpeed = maxFrc; }

	void AddForce(Vector2 force) { SetVel(Vector2Add(force, GetVel())); }

=======
>>>>>>> parent of ebb9e7f (fixed~)
	/* Boid Functions */
	bool IsPredator() { return mIsPredator; }

	Vector2 GetTargetSeek() { return mSeekTarget; }
	Vector2 GetTargetFlee() { return mFleeTarget; }

	void SetTargetSeek(Vector2 seekTarget) { mSeekTarget = seekTarget; }
	void SetTargetFlee(Vector2 fleeTarget) { mFleeTarget = fleeTarget; }
};