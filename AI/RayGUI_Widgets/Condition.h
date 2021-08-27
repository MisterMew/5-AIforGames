#pragma once

#include "Behaviour.h"
#include <string>

// condition is also a behaviour so that it can work within a behaviour tree
class Condition : public Behaviour {
public: /// Public Functions
	Condition() {}
	virtual ~Condition() {}

	virtual bool Test(Agent* agent) const = 0;

	inline virtual eBehaviourResult Execute(Agent* agent, float deltaTime) {
		if (Test(agent)) { return eBehaviourResult::Success; }
		return eBehaviourResult::Failed;
	}
};

class NotCondition : public Condition {
private: /// Private Variables
	const Condition* mCondition;

public: /// Public Functions
	NotCondition(const Condition* condition) : mCondition(condition) {}
	virtual ~NotCondition() {}

	inline virtual bool Test(Agent* agent) const { return !mCondition->Test(agent); }
};