#include "EntityObject.h"

EntityObject::EntityObject() { return; }
EntityObject::EntityObject(Vector2 pos) { EntityObject::SetPos(pos); }
EntityObject::~EntityObject() {}

void EntityObject::UpdatePosition() {
	if (mParent != nullptr) {
		mGlobalPos = mParent->mGlobalPos * mLocalPos;
	}
	else {
		mGlobalPos = GetPosL();
	}

	for (auto entity : mChildren) {
		entity->UpdatePosition();
	}
}

void EntityObject::Start() {}
void EntityObject::Update() {}
void EntityObject::Draw() {}


  /// CHILD MANAGEMENT FUNCTIONS
#pragma region [ Children Functions ]
/* Get a child from EntityObjects */
EntityObject* EntityObject::GetChild(int index) { return mChildren[index]; }

/* Return a count of all children */
int EntityObject::GetChildCount() { return sizeof(mChildren); }

/* Add a child to mEntity */
void EntityObject::AddChild(EntityObject* child) {
	child->mParent = this;
	mChildren.push_back(child);
	child->UpdatePosition();
}

/* Remove a child from mEntity */
void EntityObject::RemoveChild(EntityObject* child) {
	vector<EntityObject*>::iterator position = find(mChildren.begin(), mChildren.end(), child);
	if (position != mChildren.end()) {
		mChildren.erase(position);
		child->mParent = nullptr; //Yeet the child
	}
}

bool EntityObject::HasParent() { return mParent != nullptr; }
EntityObject* EntityObject::GetParent() { return mParent; }
#pragma endregion