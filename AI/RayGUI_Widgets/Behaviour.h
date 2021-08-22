#pragma once
#include "Agent.h"

class Agent;
class Behaviour {
public: /// Public Functions ///
	Behaviour() {}
	~Behaviour() {}

	virtual bool Update(Agent& agent, float deltaTime) = 0; // pure virtual function for executing the behaviour
	virtual const char* GetBehaviorName() = 0;
};
