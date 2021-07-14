#pragma once
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

#include "raylib.h"

/// Variables
class Entity {
	Vector2 mPosition;
	Vector2 mVelocity;
	float mSize;

public:
	Entity(Vector2 pos, Vector2 vel, float size) {
		mPosition = pos;
		mVelocity = vel;
		mSize = size;
	}

	/// Function Declarations
	void UpdateEntity();
	void RenderFish();
	void EntityDetection();

	/// Function Definitions
	Vector2 GetPos() { return mPosition; }
	Vector2 GetVel() { return mVelocity; }
	float GetSize() { return mSize; }

	void SetPos(Vector2 pos) { mPosition = pos; }
	void SetVel(Vector2 vel) { mVelocity = vel; }
	void SetSize(float size) { mSize = size; }
};
