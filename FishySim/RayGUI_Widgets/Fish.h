#pragma once
#include "Agent.h"
#include "EntitySprite.h"

class Fish : public Agent {
public:
	EntitySprite* mSprite;
	Agent* mAgent;

	Fish();
	Fish(Vector2 pos);
	Fish(float x, float y);
	~Fish();

	void Start() override;
	void Update() override;
	void Draw() override;
};

