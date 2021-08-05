#pragma once
#include "Agent.h"

class Behaviour {
public:
	Behaviour() {}
	virtual ~Behaviour() {}

	virtual bool Update(Agent* agent, float deltaTime) = 0;
};
