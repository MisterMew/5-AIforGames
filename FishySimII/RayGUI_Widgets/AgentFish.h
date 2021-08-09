#pragma once
#include "EntitySprite.h"
#include "Agent.h"

// Flocking, flee, evade //

class Fish : public Agent {
private:
	EntitySprite* mSprite;

public:
	Fish();
	Fish(Vector2 pos);
	~Fish();

	void Start() override;
	void Update(float deltaTime) override;
	void Draw() override;
};