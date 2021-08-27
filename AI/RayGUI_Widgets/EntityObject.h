#pragma once
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>

using namespace std;

enum class EntityType { objPrey, objPredator, objObstacle };

class EntityObject {
private: /// Private Varibles
	EntityObject* mParent = nullptr;
	vector<EntityObject*> mChildren;

protected: /// Protected Variables
	EntityType mEntityType = {};
	Vector2 mGlobalPos = { 0, 0 };
	Vector2 mLocalPos = { 0, 0 };
	Vector2 mVelocity = { 0, 0 };

public: /// Public Functions
	EntityObject();
	EntityObject(Vector2 position);
	~EntityObject();

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	void UpdatePosition();

	/* Get */
	inline EntityType GetEntity() { return mEntityType; }
	inline Vector2 GetPos() { return GetGlobalPos(); }
	inline Vector2 GetGlobalPos() { return mGlobalPos; }
	inline Vector2 GetLocalPos() { return mLocalPos; }
	inline Vector2 GetVel() { return mVelocity; }

    /* Set */
	inline void SetEntity(EntityType entity) { mEntityType = entity; }
	inline void SetPos(Vector2 position) { SetLocalPos(position); }
	inline void SetGlobalPos(Vector2 globalPos) { mGlobalPos = globalPos; }
	inline void SetLocalPos(Vector2 localPos) { mLocalPos = localPos; }
	inline void SetVel(Vector2 velocity) { mVelocity = velocity; }

	/* Children Functions */
	inline EntityObject* GetParent() { return mParent; }
	inline EntityObject* GetChild(int index) { return mChildren[index]; }
	inline bool HasParent() { return mParent != nullptr; }
	inline int GetChildCount() { return sizeof(mChildren); }
	void AddChild(EntityObject* child);
	void RemoveChild(EntityObject* child);
};