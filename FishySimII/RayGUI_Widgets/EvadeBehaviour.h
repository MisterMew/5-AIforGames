#pragma once
#ifndef EVADE_H
#define EVADE_H
#include "Behaviour.h"
#include <raylib.h>

class EvadeBehaviour : public Behaviour {
public:
	EvadeBehaviour();
	~EvadeBehaviour();

	void Update(Agent& agent, float deltaTime);
	inline virtual const char* GetBehaviorName() { return "Evade"; }

	// The X and Y position to use in calculations for the target to evade from
	Vector2* m_targetPosition;
	Vector2* m_targetVelocity;
};

#endif