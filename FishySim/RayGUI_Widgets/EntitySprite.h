#pragma once
#include "EntityObject.h"
#include "raylib.h"

#include <cmath>

class EntitySprite : public EntityObject {
	float mWidth = 10;
	float mHeight = 10;

public:
	EntitySprite();
	~EntitySprite();

	/// Function Declarations
	void Start() override;
	void Update() override;
	virtual void Draw();
};

