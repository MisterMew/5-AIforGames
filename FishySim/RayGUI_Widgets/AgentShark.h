#pragma once
#include "Agent.h"
#include "EntitySprite.h"

class Shark : public Agent {
public:
	EntitySprite* mSprite;

	Shark();
	Shark(Vector2 pos);
	~Shark();

	void Start() override;
	void Update() override;
	void Draw() override;
};