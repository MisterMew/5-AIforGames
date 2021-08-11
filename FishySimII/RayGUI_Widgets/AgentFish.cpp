#include "AgentFish.h"

 /// FISHY CONSTRUCTORS
/* Default Constructor */
Fish::Fish() : Fish({ 0, 0 }) { } // Calls other fish constructor

Fish::Fish(Vector2 pos) : Agent(pos) { // Calls inherited constructor
	SetPos(pos);
	mEntityType = EntityType::objFish;
	mSprite = new EntitySprite(EntityType::objFish);
	Start();
}

Fish::~Fish() {}


void Fish::Start() {
	AddChild(mSprite);
}

void Fish::Update(float deltaTime) {
	EntityObject::UpdatePosition();
	Agent::Update(deltaTime); //Agent updates MY position & velocity
}

void Fish::Draw() {
	mSprite->Draw();  //Sprite draws at MY position, since it is a child and follows me
}