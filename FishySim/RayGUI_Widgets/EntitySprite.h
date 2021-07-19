#pragma once
#include "EntityObject.h"
#include "raylib.h"

#include <cmath>

class EntitySprite : public EntityObject {
	float mWidth;
	float mHeight;

public:
	EntitySprite();
	~EntitySprite();

	/// Function Declarations
	void Start() override;
	void Update() override;
	virtual void Draw();
};

