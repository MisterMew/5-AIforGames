#pragma once
#include "raymath.h"
#include "Behaviour.h"
#include <vector>

class Behaviour;
class Agent {
private: /// Private Variables ///
	Vector2 mPosition = { 0,0 };
	Vector2 mVelocity = { 0,0 };
	Vector2 mForce = { 0,0 };
	float mMaxSpeed = 100.0F;
	float mFriction = 0.99F;

protected: /// Protected Variables ///
	std::vector<Behaviour*> mBehaviourList;

public: /// Public Functions ///
	Agent();
	~Agent();

	 // Function Declarations //
	virtual void Update(float deltaTime);
	virtual void Draw();

	void AddBehaviour(Behaviour* behaviour);

	 // Function Definitions //
	/* Get */
	Vector2 GetPos() { return mPosition; }
	Vector2 GetVel() { return mVelocity; }
	Vector2 GetForce() { return mForce; }
	float GetMaxSpeed() { return mMaxSpeed; }
	float GetFriction() { return mFriction; }

	/* Set */
	void SetPos(Vector2 position) { mPosition = position; };
	void SetVel(Vector2 velocity) { mVelocity = velocity; };
	void SetForce(Vector2 force) { mForce = force; };
	void SetMaxSpeed(float maxSpeed) { mMaxSpeed = maxSpeed; };
	void SetFriction(float friction) { mFriction = friction; };


private: /// Private Functions ///
	Vector2 Truncate(Vector2 v, float max);
};

