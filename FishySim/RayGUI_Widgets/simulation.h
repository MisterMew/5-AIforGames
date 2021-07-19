#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

#include "raylib.h"

/// Variables
class Entity {

	bool mIsPredator = false;

	Vector2 mPosition = Vector2();
	Vector2 mVelocity = Vector2();
	Vector2 mAcceleration = Vector2();
	Vector2 mTarget = Vector2();

	float mMaxSpeed = 10;
	float mSize = 0;

	float mPerceptionRadius = 0;

	float mSeperationVal = 0;
	float mAlignmentVal = 0;
	float mCohesionVal = 0;


public:
	Entity();
	Entity(Vector2 pos, Vector2 vel, float size) {
		mPosition = pos;
		mVelocity = vel;
		mSize = size;
		mAcceleration = Vector2();
	}
	Entity(Vector2 pos, Vector2 vel, bool isPredator) {
		mPosition = pos;
		mVelocity = vel;
		mAcceleration = Vector2();
		mIsPredator = isPredator;
	}

	/// Function Definitions
	bool GetPredator() { return mIsPredator == true; }
	Vector2 GetPos() { return mPosition; }
	Vector2 GetVel() { return mVelocity; } 
	Vector2 GetAcc() { return mAcceleration; }
	Vector2 GetTarget() { return mTarget; }
	float GetSize() { return mSize; }

	void SetPos(Vector2 pos) { mPosition = pos; }
	void SetVel(Vector2 vel) { mVelocity = vel; }
	void SetAcc(Vector2 acc) { mAcceleration = acc; }
	void SetTarget(Vector2 tar) { mTarget = tar; }
	void SetSize(float size) { mSize = size; }

	/// Function Declarations
	void UpdateEntity();

	void Seperate();
	void Align();
	void Cohese();

	void Seek();
	void Flee();

	void RenderFish();
	void RenderShark();
	void RenderWhale();
};

float Distance(float x1, float y1, float x2, float y2);