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
<<<<<<< HEAD
	mSprite = new EntitySprite(SpriteDrawType::SprFish);
=======
	mSprite = new EntitySprite();
>>>>>>> parent of ebb9e7f (fixed~)
	Start();
}

Fish::~Fish() {}

#pragma endregion


void Fish::Start() {
	AddChild(mSprite);
}

void Fish::Update() {
<<<<<<< HEAD
	Agent::Update(); //Agent updates MY position & velocity
	EntityObject::UpdatePosition();	
}

void Fish::Draw() {
	mSprite->Draw(); //Sprite draws at MY position, since it is a child and follows me
=======
	Agent::Update();
	EntityObject::UpdatePosition();
}

void Fish::Draw() {
	mSprite->Draw();
>>>>>>> parent of ebb9e7f (fixed~)
}