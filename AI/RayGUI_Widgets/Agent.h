#pragma once
#include "EntityObject.h"
#include "StateMachine.h"
#include "Behaviour.h"
#include "raymath.h"
#include <vector>
#include <cmath>

class Behaviour;
class Agent : public EntityObject {
private: /// Private Variables
	Vector2 mVelocity = { 0,0 };
	Vector2 mAcceleration = { 0,0 };
	Vector2 mForce = { 0,0 };
	float mMaxSpeed = 100.0F;
	float mMaxForce = 100.0F;
	float mFriction = 1.0F;

protected: /// Protected Variables
	State state;
	vector<Behaviour*> mBehaviours;

public: /// Public Functions
	Agent() : Agent({ 0, 0 }) {}
	Agent(Vector2 position) { Init(position); };
	~Agent() {};

	void Start() override {}
	void Update(float deltaTime) override;
	void Draw() override {}

	inline void AddBehaviour(Behaviour* behaviour) { mBehaviours.push_back(behaviour); }
	inline void ClearBehaviour() { mBehaviours.clear(); }

	/* Get */
	BehaviourState GetState() { return state.GetState(); } //Called from StateMachine
	inline Vector2 GetVel() { return mVelocity; }
	inline Vector2 GetAcc() { return mAcceleration; }
	inline Vector2 GetForce() { return mForce; }
	inline float GetMaxSpeed() { return mMaxSpeed; }
	inline float GetMaxForce() { return mMaxForce; }
	inline float GetFriction() { return mFriction; }

	/* Set */
	void SetState(BehaviourState stat) { state.SetState(stat); } //Called from StateMachine
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

private: /// Private Functions ///
	void Init(Vector2 position);
};

