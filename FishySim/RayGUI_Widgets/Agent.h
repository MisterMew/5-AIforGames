#pragma once
#include "EntityObject.h"
#include "raymath.h"
#include <vector>
#include <cmath>

class Agent : public EntityObject {
	 /// Variables
	bool mIsPredator;

	Vector2 mSteeringDirection;
	float mPerceptionRadius;
	float mMaxSpeed;
	float mMaxForce;


	/* Boid Variables */
	float mSeperation;
	float mAlignment;
	float mCohesion;

	Vector2 mSeekTarget;
	Vector2 mFleeTarget;

public: 
	 /// Function Declarations
	Agent();
	Agent(Vector2 pos);
	~Agent();

	void Update() override;

	/* Boid Law Functions */
	void Flock();
	Vector2 Seperate(Agent* agent);
	Vector2 Align(Agent* agent);
	Vector2 Cohese(Agent* agent);

	Vector2 Seek(const Vector2& v);
	bool Flee(Agent* agent);
	void Astar();

	/* Math Assists */
	float Vector2Magnitude(Vector2 vec);
	Vector2 Vector2Clamp(Vector2 vec, float min, float max);
	Vector2 Truncate(Vector2 v, float max);


	 /// Function Definitions
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

	/* Boid Functions */
	float GetSeperation() { return mSeperation; }
	float GetAlignment() { return mAlignment; }
	float GetCohesion() { return mCohesion; }

	void SetSeperation(float sep) { mSeperation = sep; }
	void SetAlignment(float ali) { mAlignment = ali; }
	void SetCohesion(float coh) { mCohesion = coh; }

	Vector2 GetTargetSeek() { return mSeekTarget; }
	Vector2 GetTargetFlee() { return mFleeTarget; }

	void SetTargetSeek(Vector2 seekTarget) { mSeekTarget = seekTarget; }
	void SetTargetFlee(Vector2 fleeTarget) { mFleeTarget = fleeTarget; }
};