#pragma once
#include "Agent.h"
#include "EntitySprite.h"

class Whale : public Agent {
public:
	EntitySprite* mSprite;

	Whale();
	Whale(Vector2 pos);
	~Whale();

	void Start() override;
	void Update() override;
	void Draw() override;
};