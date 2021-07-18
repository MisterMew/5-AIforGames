#include "Fish.h"

void Fish::Start() {
	SetPosL({rand() % GetScreenWidth(), rand() % GetScreenHeight()});
}

void Fish::Update() {
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		Translate({0, 1});
	}
}

void Fish::Draw() {
	mSprite->Draw();
}