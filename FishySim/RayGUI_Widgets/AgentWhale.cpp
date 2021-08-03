#include "AgentWhale.h"

/// FISHY CONSTRUCTORS
#pragma region [ Constructors ]
/* Default Constructor */
Whale::Whale() : Whale({ 0, 0 }) { } // Calls other fish constructor

Whale::Whale(Vector2 pos) : Agent(pos) { // Calls inherited constructor
	SetPos(pos);
	mAgentType = mWhale;
	mSprite = new EntitySprite(SpriteDrawType::SprWhale);
	Start();
}

Whale::~Whale() {}

#pragma endregion


void Whale::Start() {
	AddChild(mSprite);
}

void Whale::Update() {
	Agent::Update(); // Agent updates MY position & velocity
	EntityObject::UpdatePosition();
}

void Whale::Draw() {
	mSprite->Draw(); // Sprite draws at MY position, since it is a child and follows me
}