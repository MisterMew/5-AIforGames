#pragma once
#include "EntitySprite.h"
#include "Agent.h"

class Predator : public Agent {
private: /// Private Variables
	EntitySprite* mSprite;

public: /// Public Variables
	Predator();
	Predator(Vector2 pos);
	~Predator();

	void Start() override;
	void Update(float deltaTime) override;
	void Draw() override;
};

