#pragma once
#include "EntitySprite.h"
#include "Agent.h"

class Prey : public Agent {
private: /// Private Variables
	EntitySprite* mSprite;

public: /// Public Variables
	Prey();
	Prey(Vector2 pos);
	~Prey();

	void Start() override;
	void Update(float deltaTime) override;
	void Draw() override;
};

