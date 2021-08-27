#pragma once
#include "Behaviour.h"
#include <random>
#include <raylib.h>

class Wander : public Behaviour {
private: /// Private Variables
	Vector2 mTargetPos;
	float mCurrentTimeStep;
	float mAngleStep;
	float mTimeStep;

public: /// Public Functions
	Wander();
	~Wander() {};

	void Update(Agent* agent, float deltaTime) override;

	/* Get */
	inline virtual const char* GetBehaviorName() { return "Wander"; }

	inline Vector2 GetTargetPos() { return mTargetPos; }
	inline float GetCurTimeStep() { return mCurrentTimeStep; }
	inline float GetAngleStep() { return mAngleStep; }
	inline float GetTimeStep() { return mTimeStep; }

	/* Set */
	inline void SetTargetPos(Vector2 pos) { mTargetPos = pos; }
	inline void SetCurTimeStep(float cTimeStep) { mCurrentTimeStep = cTimeStep; }
	inline void SetAngleTimeStep(float angleStep) { mAngleStep = angleStep; }
	inline void SetTimeStep(float timeStep) { mTimeStep = timeStep; }
};

