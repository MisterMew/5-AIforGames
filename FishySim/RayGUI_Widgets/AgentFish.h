#pragma once
#include "Agent.h"
#include "EntitySprite.h"

class Fish : public Agent {
public:
	EntitySprite* mSprite;

	Fish();
	Fish(Vector2 pos);
	~Fish();

	void Start() override;
	void Update() override;
	void Draw() override;
};