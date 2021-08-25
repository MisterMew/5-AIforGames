#include "EntityObject.h"

EntityObject::EntityObject() { return; }
EntityObject::EntityObject(Vector2 pos) { EntityObject::SetPos(pos); }
EntityObject::~EntityObject() {}

void EntityObject::Start() {}
void EntityObject::Update(float deltaTime) {}
void EntityObject::Draw() {}

/// POSITION UPDATE
/* Update an entities relative position */
void EntityObject::UpdatePosition() {
	if (mParent != nullptr) {
		SetGlobalPos(Vector2Add(mParent->GetGlobalPos(), GetLocalPos()));
	}
	else {
		SetGlobalPos(GetLocalPos());
	}
	for (auto entity : mChildren) {
		entity->UpdatePosition();
	}
}


/// CHILD: Add
/* Add a child to a parent */
void EntityObject::AddChild(EntityObject* child) {
	child->mParent = this;
	mChildren.push_back(child);
	child->UpdatePosition();
}

/// CHILD: Remove
/* Remove a child from existence */
void EntityObject::RemoveChild(EntityObject* child) {
	vector<EntityObject*>::iterator position = find(mChildren.begin(), mChildren.end(), child);
	if (position != mChildren.end()) {
		mChildren.erase(position);
		child->mParent = nullptr; //Yeet the child
	}
}