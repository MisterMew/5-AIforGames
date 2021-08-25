#pragma once
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>

using namespace std;

enum class EntityType { objPrey, objPredator, objObstacle };
class EntityObject {
private:
	EntityObject* mParent = nullptr;
	vector<EntityObject*> mChildren;

protected:
	/// Variables
	EntityType mEntityType = {};
	Vector2 mGlobalPos = { 0, 0 };
	Vector2 mLocalPos = { 0, 0 };
	Vector2 mVelocity = { 0, 0 };

public:
	EntityObject();
	EntityObject(Vector2 position);
	~EntityObject();

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	void UpdatePosition();

	/// Function Definitions:
   /* SET Functions */
	void SetEntity(EntityType entity) { mEntityType = entity; }
	void SetPos(Vector2 position) { SetLocalPos(position); }
	void SetGlobalPos(Vector2 globalPos) { mGlobalPos = globalPos; }
	void SetLocalPos(Vector2 localPos) { mLocalPos = localPos; }
	void SetVel(Vector2 velocity) { mVelocity = velocity; }

	/* GET Functions */
	EntityType GetEntity() { return mEntityType; }
	Vector2 GetPos() { return GetGlobalPos(); }
	Vector2 GetGlobalPos() { return mGlobalPos; }
	Vector2 GetLocalPos() { return mLocalPos; }
	Vector2 GetVel() { return mVelocity; }

	/* Children Functions */
	EntityObject* GetParent() { return mParent; }
	EntityObject* GetChild(int index) { return mChildren[index]; }
	bool HasParent() { return mParent != nullptr; }
	int GetChildCount() { return sizeof(mChildren); }
	void AddChild(EntityObject* child);
	void RemoveChild(EntityObject* child);
};