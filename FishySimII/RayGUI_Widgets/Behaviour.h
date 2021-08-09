#pragma once
#include "Agent.h"

class Agent;
class Behaviour {
public:
	Behaviour() {}
	virtual ~Behaviour() = 0 {};

	virtual void Update(Agent& agent, float deltaTime) = 0;
	virtual const char* GetBehaviorName() = 0;
};
