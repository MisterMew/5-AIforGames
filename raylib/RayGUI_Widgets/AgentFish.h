#pragma once
#include "Agent.h"

// Flocking, flee, evade //

class Fish : public Agent {
public:
	Fish();
	Fish(Vector2 pos);
	~Fish();
};