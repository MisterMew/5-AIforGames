#pragma once
#include "Behaviour.h"
#include "Obstacle.h"
#include "Agent.h"
#include <raylib.h>
#include <vector>

class Obstacle;
class Avoid : public Behaviour {
public:
	Avoid();
	~Avoid();

	void Update(Agent& agent, float deltaTime) override;
	inline virtual const char* GetBehaviorName() { return "Avoid"; }

	float mMaxSeeAhead;
	float mMaxAvoidForce;

	Vector2* mTargetPosition;
	Vector2 mAheadPosition;
	Vector2 mAheadPosition2;

	std::vector<Obstacle*>* mObstacles;
};