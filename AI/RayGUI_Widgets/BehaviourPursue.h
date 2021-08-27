#pragma once
#include "Behaviour.h"
#include <raylib.h>
#include "Node.h"

class Pursue : public Behaviour {
private: /// Private Variables
	Vector2 mTargetPos = Vector2();
	Vector2 mTargetVel = Vector2();

public: /// Public Functions
	Pursue() {};
	~Pursue() {};

	void Update(Agent* agent, float deltaTime) override;

	/* Get */
	inline virtual const char* GetBehaviorName() { return "Pursue"; }

	inline Vector2 GetTargetPos() { return mTargetPos; }
	inline Vector2 GetTargetVel() { return mTargetVel; }

	/* Set */
	inline void SetTargetVel(Vector2 vel) { mTargetVel = vel; }
	void SetTargetPos(Agent* agent, Vector2 pos);
};

