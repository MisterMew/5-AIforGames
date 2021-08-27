#include "EntitySprite.h"

EntitySprite::EntitySprite(EntityType entityType) : mEntityType(entityType) {}
EntitySprite::~EntitySprite() {}

void EntitySprite::Start() {}
void EntitySprite::Update(float deltaTime) {}

/* Choose which sprite to render */
void EntitySprite::Draw() {
	if (!HasParent()) { return; }

	switch (mEntityType) {
	case EntityType::objPrey:
		RenderPrey();
		break;

	case EntityType::objPredator:
		RenderPredator();
		break;

	default: break;
	}
}

#pragma region [ Sprite Rendering ]

 /// RENDER: Prey
/* Renders the sprite for the prey */
void EntitySprite::RenderPrey() {
	DrawPoly(GetPos(), 5, 5, 0, PALEGREENa);
	DrawPolyLines(GetPos(), 5, 6, 0, PALEGREEN);
}

 /// RENDER: Predator
/* Renders the sprite for the Predator */
void EntitySprite::RenderPredator() {
	DrawPoly(GetPos(), 5, 5, 0, PALEREDa);
	DrawPolyLines(GetPos(), 5, 6, 0, PALERED);
}

#pragma endregion