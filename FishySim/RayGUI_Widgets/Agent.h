#pragma once
#include "EntityObject.h"
#include "raymath.h"
#include <vector>
#include <cmath>

/// TO DO:
// SEPERATION: Steer to avoid collision/crowding with flockmates
// ALIGNMENT: Steer towards average heading of flockmates
// COHESION: Steer to move towards the average position (centre of mass) of local flockmates 

// SEEK: Moving towards a target
// FLEE: Evading a target
// WANDER: Moving anywhere

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
	Vector2 Seperate(Agent* agent);
	Vector2 Align(Agent* agent);
	Vector2 Cohese(Agent* agent);

	/* AI Functions */
	Vector2 Seek(const Vector2& v);
	void Flee();
	void Astar();

	/* Assists */
	float Vector2Magnitude(Vector2 vec);
	Vector2 Vector2Clamp(Vector2 vec, float min, float max);


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