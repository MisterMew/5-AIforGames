#pragma once
#include "Behaviour.h"

class FleeBehaviour : public Behaviour {
private:
	Vector2 mDestination;
	float mFleeRadius = 100;

public:
	FleeBehaviour() {};
	virtual ~FleeBehaviour() {};

	virtual bool Update(Agent* agent, float deltaTime);
	void SetDestination(Vector2 destination) { mDestination = destination; }
};

