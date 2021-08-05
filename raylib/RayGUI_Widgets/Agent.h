#pragma once
#include "raymath.h"
#include "raylib.h"
#include <vector>

class Behaviour;

class Agent {
private:
	Vector2 Truncate(Vector2 v, float max);

protected:
	std::vector<Behaviour*> mBehaviourList;

	Vector2 mPosition = { 0, 0 };
	Vector2 mVelocity = { 0, 0 };
	Vector2 mAcceleration = { 0, 0 };
	Vector2 mForce = { 0, 0 };
	float mMaxSpeed = 100;
	float mMaxForce = 100;
	float mFriction = 0.99; //0 = no friction, 1 = max friction

	float mRotation = 0;
	float mRotDampening = 0;

public:
	Agent();
	Agent(Vector2 position);
	virtual ~Agent();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void AddBehaviour(Behaviour* behaviour);

	/// Function Definitions:
	void SetPos(Vector2 position) { mPosition = position; }
	void SetVel(Vector2 velocity) { mVelocity = velocity; }
	void SetAcc(Vector2 acceleration) { mAcceleration = acceleration; }
	void SetForce(Vector2 force) { mForce = force; }
	void SetMaxSpeed(float speed) { mMaxSpeed = speed; }
	void SetMaxForce(float force) { mMaxForce = force; }
	void SetFriction(float friction) { mFriction = friction; }

	void SetRotation(float rotation) { mRotation = rotation; }
	void SetRotDampening(float rotDampening) { mRotDampening = rotDampening; }

	Vector2 GetPosition() { return mPosition; }
	Vector2 GetVelocity() { return mVelocity; }
	Vector2 GetAcceleration() { return mAcceleration; }
	Vector2 GetForce() { return mForce; }
	float GetMaxSpeed() { return mMaxSpeed; }
	float GetMaxForce() { return mMaxForce; }
	float GetFriction() { return mFriction; }

	float GetRotation() { return mRotation; }
	float GetRotDampening() { return mRotDampening; }

	void AddForce(Vector2 force) { mForce = Vector2Add(force, mForce); }
};


