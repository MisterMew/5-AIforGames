#pragma once
#include "EntityObject.h"
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <cmath>

enum class SpriteDrawType { SprFish, SprShark, SprWhale };

class EntitySprite : public EntityObject {
	float mWidth = 10;
	float mHeight = 10;

	SpriteDrawType mDrawType;
	Vector2 head, tail, left, right;


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

	Vector2 GetDrawPoints(float h, float t, float L, float R);
	void DrawRectangleLinesPro(Rectangle rec, Vector2 origin, float rotation, Color color);
	float Vector2Mag(Vector2 vec);
};

