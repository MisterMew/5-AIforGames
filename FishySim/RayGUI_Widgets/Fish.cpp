#include "Fish.h"

Fish::Fish() { mSprite = new EntitySprite(); }

Fish::Fish(Vector2 pos) { 
	Translate(pos); 
	mSprite = new EntitySprite();
}

Fish::Fish(float x, float y) { 
	Translate({ x, y });
	mSprite = new EntitySprite();
}

Fish::~Fish() {}


void Fish::Start() {
	AddChild(mSprite);
}

void Fish::Update() {
	mSprite->Update();

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		Translate({0, 1});
	}
}

void Fish::Draw() {
	mSprite->Draw();
}