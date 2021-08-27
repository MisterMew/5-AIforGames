#pragma once
#include "EntityObject.h"

#include "CustomColours.h"
#include "raymath.h"
#include "raylib.h"

#include <vector>
#include <cmath>

class EntitySprite : public EntityObject {
private: /// Private Variables
	EntityType mEntityType;

public: /// Public Functions
	EntitySprite(EntityType mDrawEntity);
	~EntitySprite();


	void Start() override;
	void Update(float deltaTime) override;
	virtual void Draw();

	void RenderPrey();
	void RenderPredator();
};

