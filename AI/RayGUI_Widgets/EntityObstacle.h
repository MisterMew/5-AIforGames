#pragma once
#include "CustomColours.h"
#include <raylib.h>

class Obstacle {
private: /// Private Variables
	Vector2 mPosition = { 0, 0 };
	unsigned const int mSize = 20;

public: /// Public Variables
	Obstacle();
	Obstacle(Vector2 position);
	~Obstacle();

	void Update();
	void Draw();

	/* Get */
	inline Vector2 GetPos() { return mPosition; }
	inline int GetSize() { return mSize; }

	/* Set */
	inline void SetPos(Vector2 position) { mPosition = position; }
};