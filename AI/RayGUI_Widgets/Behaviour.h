#pragma once

class Agent;
class Behaviour {
public: /// Public Functions
	Behaviour() {};
	virtual ~Behaviour() = 0 {};

	virtual void Update(Agent* agent, float deltaTime) = 0;
	virtual const char* GetBehaviorName() = 0;
};