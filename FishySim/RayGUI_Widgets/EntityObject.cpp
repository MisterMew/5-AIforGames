#include "EntityObject.h"

EntityObject::EntityObject() { return; }
EntityObject::EntityObject(Vector2 pos) { EntityObject::SetPos(pos); }
EntityObject::~EntityObject() {}

void EntityObject::UpdatePosition() {
	if (mEntity != nullptr) {
		mGlobalPos = mEntity->mGlobalPos * mLocalPos;
	}
	else {
		mGlobalPos = GetPosL();
	}

	for (auto entity : mEntityChildren) {
		entity->UpdatePosition();
	}
}

void EntityObject::Start() {}
void EntityObject::Update() {}
void EntityObject::Draw() {}


  /// CHILD MANAGEMENT FUNCTIONS
#pragma region [ Children Functions ]
/* Get a child from EntityObjects */
EntityObject* EntityObject::GetChild(int index) { return mEntityChildren[index]; }

/* Return a count of all children */
int EntityObject::GetChildCount() { return sizeof(mEntityChildren); }

/* Add a child to mEntity */
void EntityObject::AddChild(EntityObject* child) {
	child->mEntity = this;
	mEntityChildren.push_back(child);
	child->UpdatePosition();
}

/* Remove a child from mEntity */
void EntityObject::RemoveChild(EntityObject* child) {
	vector<EntityObject*>::iterator position = find(mEntityChildren.begin(), mEntityChildren.end(), child);
	if (position != mEntityChildren.end()) {
		mEntityChildren.erase(position);
		child->mEntity = nullptr; //Yeet the child
	}
}
#pragma endregion