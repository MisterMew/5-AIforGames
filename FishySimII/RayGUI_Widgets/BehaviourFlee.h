#pragma once
#include "Behaviour.h"
#include "Agent.h"

class FleeBehaviour : public Behaviour {
private:
	Vector2* mTargetPosition;

public:
	FleeBehaviour();
	virtual ~FleeBehaviour();

	void Update(Agent& agent, float deltaTime) override;
	inline virtual const char* GetBehaviorName() { return "Flee"; }

	void SetTargetPosition(Vector2* destination) { mTargetPosition = destination; }

};