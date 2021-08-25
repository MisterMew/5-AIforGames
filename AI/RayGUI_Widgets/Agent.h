#pragma once
#include "raymath.h"
#include "EntityObject.h"
#include "Behaviour.h"

#include <iostream>
#include <vector>
#include <cmath>

class Behaviour;
class Agent : public EntityObject {
private: /// Private Variables ///
	Vector2 mPosition = { 0,0 };
	Vector2 mVelocity = { 0,0 };
	Vector2 mAcceleration = { 0,0 };
	Vector2 mForce = { 0,0 };
	float mMaxSpeed = 100.0F;
	float mMaxForce = 100;
	float mFriction = 0.99F;

protected: /// Protected Variables ///
	std::vector<Behaviour*> mBehaviours;

public: /// Public Functions ///
	Agent();
	Agent(Vector2 position);
	~Agent();

	 // Function Declarations //
	void Start() override {}
	void Update(float deltaTime) override;
	void Draw() override {}

	inline void AddBehaviour(Behaviour* behaviour) { mBehaviours.push_back(behaviour); }
	inline void ClearBehaviour() { mBehaviours.clear(); }

	 // Function Definitions //
	/* Get */
	inline Vector2 GetPos() { return mPosition; }
	inline Vector2 GetVel() { return mVelocity; }
	inline Vector2 GetAcc() { return mAcceleration; }
	inline Vector2 GetForce() { return mForce; }
	inline float GetMaxSpeed() { return mMaxSpeed; }
	inline float GetMaxForce() { return mMaxForce; }
	inline float GetFriction() { return mFriction; }

	/* Set */
	inline void SetPos(Vector2 position) { mPosition = position; };
	inline void SetVel(Vector2 velocity) { mVelocity = velocity; };
	inline void SetAcc(Vector2 acceleration) { mAcceleration = acceleration; }
	inline void SetForce(Vector2 force) { mForce = force; }
	inline void SetMaxSpeed(float speed) { mMaxSpeed = speed; }
	inline void SetMaxForce(float force) { mMaxForce = force; }
	inline void SetFriction(float friction) { mFriction = friction; };

	/* ADD Functions */
	inline void AddVel(Vector2 vel) { mVelocity = Vector2Add(mVelocity, vel); }
	inline void AddAcc(Vector2 acc) { mAcceleration = Vector2Add(mAcceleration, acc); }
	inline void AddForce(Vector2 force) { mForce = Vector2Add(force, mForce); }

	/* Vector2 Math Operations */
	Vector2 Vector2Truncate(Vector2 vector, float max);
	static Vector2 Vector2Clamp(Vector2 vector, float clampMin, float clampMax);
	static float Vector2Magnitude(Vector2 vector);

	void WrapScreenBounds(Vector2* pos);

private: /// Private Functions ///
	void Init(Vector2 position);
};

