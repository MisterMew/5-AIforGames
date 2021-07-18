#pragma once
#include "EntityObject.h"
#include "raylib.h"

#include <cmath>

class EntitySprite : EntityObject {
	float mWidth;
	float mHeight;
public:
	void Start() override;
	void Update() override;
	virtual void Draw() = 0;
};

