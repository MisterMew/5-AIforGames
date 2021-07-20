#include "AgentFish.h"

  /// FISHY CONSTRUCTORS
#pragma region [ Constructors ]
/* Default Constructor */
Fish::Fish() { 
	mSprite = new EntitySprite(); 
	Start();
}

Fish::Fish(Vector2 pos) { 
	SetPos(pos); 
	mSprite = new EntitySprite();
	Start();
}

Fish::~Fish() {}

#pragma endregion


void Fish::Start() {
	AddChild(mSprite);
}

void Fish::Update() {
	Agent::Update();
	EntityObject::UpdatePosition();
}

void Fish::Draw() {
	mSprite->Draw();
}