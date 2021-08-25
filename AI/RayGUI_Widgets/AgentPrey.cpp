#include "AgentPrey.h"

 /// PREY CONSTRUCTORS
/* Default Constructors */
Prey::Prey() : Prey({ 0, 0 }) {}
Prey::Prey(Vector2 pos) : Agent(pos) {
	SetPos(pos);
	mEntityType = EntityType::objPrey;
	mSprite = new EntitySprite(EntityType::objPrey);
	Start();
}

Prey::~Prey() {}


void Prey::Start() {
	AddChild(mSprite);
}

void Prey::Update(float deltaTime) {
	EntityObject::UpdatePosition();
	Agent::Update(deltaTime); //Agent updates MY position & velocity
}

void Prey::Draw() {
	mSprite->Draw();  //Sprite draws at MY position, since it is a child and follows me
}