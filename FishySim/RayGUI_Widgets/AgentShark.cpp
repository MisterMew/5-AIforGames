#include "AgentShark.h"
<<<<<<< HEAD:FishySim/RayGUI_Widgets/AgentShark.cpp

  /// SHARKY CONSTRUCTORS
#pragma region [ Constructors ]
/* Default Constructor */
Shark::Shark() : Shark({ 0, 0 }) { } // Calls other shark constructor

Shark::Shark(Vector2 pos) : Agent(pos) { // Calls inherited constructor
	SetPos(pos);
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
=======
>>>>>>> parent of ebb9e7f (fixed~):FishySim/RayGUI_Widgets/Shark.cpp
