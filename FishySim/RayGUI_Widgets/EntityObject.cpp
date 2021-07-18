#include "EntityObject.h"

EntityObject::EntityObject() {}
EntityObject::~EntityObject() {}

void EntityObject::UpdatePosition() {
	if (entity != nullptr) {
		mGlobalPos = entity->GetPosG() * GetPosL();
	}
	else {
		mGlobalPos = GetPosL();
	}

	for (auto entity : entityChild) {
		entity.UpdatePosition();
	}
}