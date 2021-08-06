#pragma once
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>

using namespace std;

enum class EntityType { objFish, objShark, objWhale };
class EntityObject {
private:
	EntityObject* mParent = nullptr;
	vector<EntityObject*> mChildren;

protected:
	/// Variables
	EntityType mEntity;
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
	EntityObject();
	EntityObject(Vector2 position);
	~EntityObject();

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	void UpdatePosition();

	 /// Function Definitions:
	/* SET Functions */
	void SetEntity(EntityType entity) { mEntity = entity; }
	void SetPos(Vector2 position) { mPosition = position; }
	void SetVel(Vector2 velocity) { mVelocity = velocity; }
	void SetAcc(Vector2 acceleration) { mAcceleration = acceleration; }
	void SetForce(Vector2 force) { mForce = force; }
	void SetMaxSpeed(float speed) { mMaxSpeed = speed; }
	void SetMaxForce(float force) { mMaxForce = force; }
	void SetFriction(float friction) { mFriction = friction; }
	void SetRotation(float rotation) { mRotation = rotation; }
	void SetRotDampening(float rotDampening) { mRotDampening = rotDampening; }

	/* GET Functions */
	EntityType GetEntity() { return mEntity; }
	Vector2 GetPos() { return mPosition; }
	Vector2 GetVel() { return mVelocity; }
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

	/* Children Functions */
	EntityObject* GetParent() { return mParent; }
	EntityObject* GetChild(int index) { return mChildren[index]; }
	bool HasParent() { return mParent != nullptr; }
	void AddChild(EntityObject* child);
	void RemoveChild(EntityObject* child);
};