#include "AgentFish.h"

  /// FISHY CONSTRUCTORS
#pragma region [ Constructors ]
/* Default Constructor */
Fish::Fish() : Fish({ 0, 0 }) { } // Calls other fish constructor

Fish::Fish(Vector2 pos) : Agent(pos) { // Calls inherited constructor
	SetPos(pos); 
	mSprite = new EntitySprite(SpriteDrawType::SprFish);
	Start();
}

Fish::~Fish() {}

#pragma endregion


void Fish::Start() {
	AddChild(mSprite);
}

void Fish::Update() {
	Agent::Update(); //Agent updates MY position & velocity
	EntityObject::UpdatePosition();	
}

void Fish::Draw() {
	mSprite->Draw(); //Sprite draws at MY position, since it is a child and follows me
}