#pragma once
#include "Behaviour.h"
#include "Obstacle.h"
#include "Agent.h"
#include <raylib.h>
#include <vector>

class Obstacle;
class AvoidBehaviour : public Behaviour {
private:
	float mMaxSeeAhead;
	float mMaxAvoidForce;

	Vector2* mTargetPosition;
	Vector2 mAheadPosition;
	Vector2 mAheadPosition2;

public:
	AvoidBehaviour();
	~AvoidBehaviour();

	void Update(Agent& agent, float deltaTime) override;
	inline virtual const char* GetBehaviorName() { return "Avoid"; }

	vector<Obstacle*> *mObstacles;
	
	void SetTargetPosition(Vector2* destination) { mTargetPosition = destination; }

private:
	void Init();
};