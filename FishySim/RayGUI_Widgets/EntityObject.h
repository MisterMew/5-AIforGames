#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Matrix3.h"
#include <iostream>
#include <vector>

using namespace std;

class EntityObject {
	EntityObject* mEntity = nullptr;
	vector<EntityObject*> mEntityChildren;
	
	/// Entity Variables
	Matrix3 mLocalPos;
	Matrix3 mGlobalPos;

	/* Movement Variables */
	Vector2 mVelocity = {10, 10};
	Vector2 mAcceleration;

public:
	EntityObject();
	EntityObject(Vector2 pos);
	~EntityObject();

	/// Function Declarations
	void UpdatePosition();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	/* Children Functions */
	EntityObject* GetChild(int index);
	int GetChildCount();
	void AddChild(EntityObject* child);
	void RemoveChild(EntityObject* child);


	 /// Function Definitions
	/* Get Position Functions */
	Vector2 GetPos() { return { mGlobalPos.m7, mGlobalPos.m8 }; }
	Matrix3 GetPosL() { return mLocalPos; }
	Matrix3 GetPosG() { return mGlobalPos; }

	Vector2 GetVel() { return mVelocity; }
	Vector2 GetAcc() { return mAcceleration; }

	/* Set Position Functions */
	void SetPos(Vector2 pos) { SetPosL(pos); UpdatePosition(); }
	void SetPosL(Vector2 pos) { mLocalPos.SetTranslate(pos.x, pos.y); UpdatePosition(); }
	void SetPosG(Vector2 pos) { mGlobalPos.SetTranslate(pos.x, pos.y); UpdatePosition(); }

	void SetVel(Vector2 vel) { mVelocity = vel; }
	void SetAcc(Vector2 acc) { mAcceleration = acc; }

	void AddVel(Vector2 vel) { mVelocity = Vector2Add(mVelocity, vel); }
	void AddAcc(Vector2 acc) { mAcceleration = Vector2Add(mAcceleration, acc); }

	/* Rotation & Translation Functions*/
	void Translate(Vector2 pos) { mLocalPos.Translate(pos.x, pos.y); UpdatePosition(); }
	void SetRot(float radians) { mLocalPos.SetRotateZ(radians); UpdatePosition(); }
	void Rotate(float radians) { mLocalPos.RotateZ(radians); UpdatePosition(); }
};