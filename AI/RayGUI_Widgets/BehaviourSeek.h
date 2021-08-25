#pragma once
#include "Behaviour.h"
#include "Agent.h"

class SeekBehaviour : public Behaviour {
private:
	Vector2* mTargetPosition;

public:
	SeekBehaviour();
	virtual ~SeekBehaviour();

	void Update(Agent& agent, float deltaTime) override;
	inline virtual const char* GetBehaviorName() { return "Seek"; }

	void SetTargetPosition(Vector2* destination) { mTargetPosition = destination; }

};