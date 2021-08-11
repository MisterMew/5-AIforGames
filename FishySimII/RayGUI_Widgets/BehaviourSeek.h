#pragma once
#include "Behaviour.h"
#include "Agent.h"
#include <raylib.h>

class Seek : public Behaviour {
public:
	Seek();
	virtual ~Seek();

	virtual void Update(Agent& agent, float deltaTime);
	inline virtual const char* GetBehaviorName() { return "Seek"; }
	void SetDestination(Vector2* target) { mTargetPosition = target; }

	// X and Y position to seek towards
	Vector2* mTargetPosition;
};