#pragma once
#include "EntityObject.h"
#include "Behaviour.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include <cmath>

class Behaviour;
class Agent : public EntityObject {
private:
	Vector2 mPositionReset = { 0, 0 };
	vector<Behaviour*> mBehaviours;

protected:
	vector<Agent*>* mAgents = {};

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
	~Agent();

	void Update(float deltaTime) override;

	void AddBehaviour(Behaviour* behaviour) { mBehaviours.push_back(behaviour); }


	 /// Function Definitions:
    /* SET Functions */
	void SetAcc(Vector2 acceleration) { mAcceleration = acceleration; }
	void SetForce(Vector2 force) { mForce = force; }
	void SetMaxSpeed(float speed) { mMaxSpeed = speed; }
	void SetMaxForce(float force) { mMaxForce = force; }
	void SetFriction(float friction) { mFriction = friction; }
	void SetRotation(float rotation) { mRotation = rotation; }
	void SetRotDampening(float rotDampening) { mRotDampening = rotDampening; }

	/* GET Functions */
	Vector2 GetAcc() { return mAcceleration; }
	Vector2 GetForce() { return mForce; }
	float GetMaxSpeed() { return mMaxSpeed; }
	float GetMaxForce() { return mMaxForce; }
	float GetFriction() { return mFriction; }
	float GetRotation() { return mRotation; }
	float GetRotDampening() { return mRotDampening; }

	/* ADD Functions */
	void AddVel(Vector2 vel) { mVelocity = Vector2Add(mVelocity, vel); }
	void AddAcc(Vector2 acc) { mAcceleration = Vector2Add(mAcceleration, acc); }
	void AddForce(Vector2 force) { mForce = Vector2Add(force, mForce); }

	/* Vector2 Math Operations */
	Vector2 Vector2Truncate(Vector2 vector, float max);
	Vector2 Vector2Clamp(Vector2 vector, float clampMin, float clampMax);
	float Vector2Magnitude(Vector2 vector);

private:
	void Init(Vector2 position);
	void AvoidEntities();
	void WrapScreenBounds(Vector2* pos);
};