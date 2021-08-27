#pragma once
#include "Behaviour.h"
#include <raylib.h>

class Flee : public Behaviour {
private: /// Private Variables
	Vector2 mTargetPos;

public: /// Public Functions
	Flee() {};
	virtual ~Flee() {};

	virtual void Update(Agent* agent, float deltaTime) override;
	
	/* Get */
	inline virtual const char* GetBehaviorName() { return "Flee"; }
	inline Vector2 GetTargetPos() { return mTargetPos; }

	/* Set */
	inline void SetTargetPos(Vector2 pos) { mTargetPos = pos; }
};

