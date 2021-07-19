#pragma once
#include "EntityObject.h"

/// TO DO:
// SEPERATION: Steer to avoid collision/crowding with flockmates
// ALIGNMENT: Steer towards average heading of flockmates
// COHESION: Steer to move towards the average position (centre of mass) of local flockmates 

// SEEK: Moving towards a target
// FLEE: Evading a target
// WANDER: Moving anywhere

class Agent : public EntityObject {
	/// Variables
	/* Boid Variables */
	bool mIsPredator;

	float mSeperation;
	float mAlignment;
	float mCohesion;

	Vector2 mSeekTarget;
	Vector2 mFleeTarget;

	/* Movement Variables */
protected:
	Vector2 mVelocity = {5, 5};
	Vector2 mAcceleration = {2, 2};

public: 
	 /// Function Declarations
	void Update() override;

	/* Boid Law Functions */
	void Seperate();
	void Align();
	void Cohese();

	/* AI Functions */
	void Seek();
	void Flee();


	 /// Function Definitions
	/* Boid Functions */
	bool IsPredator() { return mIsPredator; }

	Vector2 GetTargetSeek() { return mSeekTarget; }
	Vector2 GetTargetFlee() { return mFleeTarget; }

	void SetTargetSeek(Vector2 seekTarget) { mSeekTarget = seekTarget; }
	void SetTargetFlee(Vector2 fleeTarget) { mFleeTarget = fleeTarget; }

	/* Movement Functions */
	Vector2 GetVel() { return mVelocity; }
	Vector2 GetAcc() { return mAcceleration; }

	void SetVel(Vector2 vel) { mVelocity = vel; }
	void SetAcc(Vector2 acc) { mAcceleration = acc; }
};