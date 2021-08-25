#include "AgentPredator.h"

/// PREY CONSTRUCTORS
/* Default Constructors */
Predator::Predator() : Predator({ 0, 0 }) {}
Predator::Predator(Vector2 pos) : Agent(pos) {
	SetPos(pos);
	mEntityType = EntityType::objPredator;
	mSprite = new EntitySprite(EntityType::objPredator);
	Start();
}

Predator::~Predator() {}


void Predator::Start() {
	AddChild(mSprite);
}

void Predator::Update(float deltaTime) {
	EntityObject::UpdatePosition();
	Agent::Update(deltaTime); //Agent updates MY position & velocity
}

void Predator::Draw() {
	mSprite->Draw();  //Sprite draws at MY position, since it is a child and follows me
}