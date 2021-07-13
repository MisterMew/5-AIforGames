#pragma once

#include "raylib.h"

/// Variables
class Entity {
	Color mColor = MAGENTA;
	Vector2 mCentre = { (GetScreenWidth() / 2.0f) , (GetScreenHeight() / 2.0f) };
	Vector2 mPosition;
	Vector2 mVelocity;
	float mMaxSpeed;
	float mDetectionRadius;

	struct Fish {};
	struct Shark {};
	struct Whale {};

public:
	/// Function Declarations
	void SpawnEntity();
	void DrawEntity();

	/// Function Definitions
	Vector2 GetCentre() { return mCentre; }
	Vector2 GetPosition() { return mPosition; }
	Color GetColor() { return mColor; }

	void SetPosition(Vector2 position) { mPosition = position; }
	void SetColor(Color color) { mColor = color; }
};
