#include "AgentShark.h"

  /// SHARKY CONSTRUCTORS
#pragma region [ Constructors ]
/* Default Constructor */
Shark::Shark() : Shark({ 0, 0 }) { } // Calls other shark constructor

Shark::Shark(Vector2 pos) : Agent(pos) { // Calls inherited constructor
	SetPos(pos);
	mAgentType = AgentType::mShark;
	mSprite = new EntitySprite(SpriteDrawType::SprShark);
	Start();
}

Shark::~Shark() {}

#pragma endregion


void Shark::Start() {
	AddChild(mSprite);
}

void Shark::Update() {
	Agent::Update(); //Agent updates MY position & velocity
	EntityObject::UpdatePosition();
}

void Shark::Draw() {
	mSprite->Draw(); //Sprite draws at MY position, since it is a child and follows me
}