#pragma once
#include "EntityObject.h"
#include "raymath.h"
#include "raylib.h"
#include <vector>
#include <cmath>

class EntitySprite : public EntityObject {
private:
	EntityType mEntityType;
	Vector2 head, tail, left, right;

public:
	EntitySprite();
	EntitySprite(EntityType mDrawEntity);
	~EntitySprite();

	/// Function Declarations
	void Start() override;
	void Update(float deltaTime) override;
	virtual void Draw();

	void RenderFish();
	void RenderShark();
	void RenderWhale();
	void RenderBubble();

	Vector2 GetDrawPoints(float h, float t, float L, float R);
};

