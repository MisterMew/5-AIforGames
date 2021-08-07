#pragma once
#include "Behaviour.h"
#include "Agent.h"
#include <raylib.h>
#include <random>

class Wander : public Behaviour {
private:
	Vector2 mTargetPosition;
	float mCurrentTimeStepping;

	void Init();

public:
	Wander();
	virtual ~Wander();

	virtual void Update(Agent& agent, float deltaTime);
	inline virtual const char* GetBehaviorName() { return "Wander"; }

	float mAngleStepping;
	float mTimeStepping;

	 /// Function Definitions
	/* SET Functions */
	void SetTargetPos(Vector2 targetpos) { mTargetPosition = targetpos; }
	void SetCurrentTimeStepping(float currenttime) { mCurrentTimeStepping = currenttime; }
	void SetTimeStepping(float timestep) { mTimeStepping = timestep; }
	void SetAngleStepping(float anglestep) { mAngleStepping = anglestep; }

	/* GET Functions */
	Vector2 GetTargetPos() { return mTargetPosition; }
};
