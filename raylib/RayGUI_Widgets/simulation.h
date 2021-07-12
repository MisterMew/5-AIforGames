#pragma once

#include <iostream>
#include <string>

using namespace std;

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#define RAYGUI_STATIC

#include "raylib.h"
#include "raygui.h"

#undef RAYGUI_IMPLEMENTATION


/// Variables
class Entity {
	Vector2 mPos;
	Vector2 mSpeed;
	Color color;
	float mRadius;

	struct Fish {};
	struct Shark {};
	struct Whale {};
};

/// Function Declarations