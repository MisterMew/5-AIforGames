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

public: 
	 /// Function Declarations
	Agent();
	Agent(Vector2 pos);
	~Agent();

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
};