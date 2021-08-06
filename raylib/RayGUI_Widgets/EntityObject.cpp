#include "EntityObject.h"

EntityObject::EntityObject() { return; }
EntityObject::EntityObject(Vector2 pos) { EntityObject::SetPos(pos); }
EntityObject::~EntityObject() {}

void EntityObject::UpdatePosition() {
	for (auto entity : mChildren) {
		entity->UpdatePosition();
	}
}

void EntityObject::Start() {}
void EntityObject::Update(float deltaTime) {}
void EntityObject::Draw() {}

void EntityObject::AddChild(EntityObject* child) {
	child->mParent = this;
	mChildren.push_back(child);
	child->UpdatePosition();
}

void EntityObject::RemoveChild(EntityObject* child) {
	vector<EntityObject*>::iterator position = find(mChildren.begin(), mChildren.end(), child);
	if (position != mChildren.end()) {
		mChildren.erase(position);
		child->mParent = nullptr; //Yeet the child
	}
}