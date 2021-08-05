#pragma once
#include "Behaviour.h"

class SeekBehaviour : public Behaviour {
private:
	Vector2 mDestination;

public:
	SeekBehaviour() {};
	virtual ~SeekBehaviour() {};

	virtual bool Update(Agent* agent, float deltaTime);
	void SetDestination(Vector2 destination) { mDestination = destination; }
};

