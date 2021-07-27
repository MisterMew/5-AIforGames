#pragma once
#include "EntityObject.h"
#include "raylib.h"

#include <cmath>

enum class SpriteDrawType { SprFish, SprShark, SprWhale };

class EntitySprite : public EntityObject {
	float mWidth = 10;
	float mHeight = 10;

	SpriteDrawType mDrawType;

public:
	EntitySprite(SpriteDrawType drawType);
	~EntitySprite();

	/// Function Declarations
	void Start() override;
	void Update() override;
	virtual void Draw();

	void RenderFish();
	void RenderShark();
	void RenderWhale();
};

