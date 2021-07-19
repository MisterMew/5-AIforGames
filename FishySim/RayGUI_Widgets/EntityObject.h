#pragma once
#include "raylib.h"
#include "Matrix3.h"
#include <vector>
#include <iostream>

using namespace std;

class EntityObject {
	EntityObject* mEntity = nullptr;
	vector<EntityObject*> mEntityChildren;
	
	/// Entity Variables
	Vector2 mPosition = {50, 50};
	Matrix3 mLocalPos;
	Matrix3 mGlobalPos;

public:
	EntityObject();
	EntityObject(Vector2 pos);
	~EntityObject();

	/// Function Declarations
	void UpdatePosition();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	/* Children Functions */
	EntityObject* GetChild(int index);
	int GetChildCount();
	void AddChild(EntityObject* child);
	void RemoveChild(EntityObject* child);


	 /// Function Definitions
	/* Get Position Functions */
	Vector2 GetPos() { return { mGlobalPos.m7, mGlobalPos.m8 }; }
	Matrix3 GetPosL() { return mLocalPos; }
	Matrix3 GetPosG() { return mGlobalPos; }

	/* Set Position Functions */
	void SetPos(Vector2 pos) { mPosition.x = mLocalPos.m7, mPosition.y = mLocalPos.m8; UpdatePosition(); }
	void SetPosL(Vector2 pos) { mLocalPos.SetTranslate(pos.x, pos.y); UpdatePosition(); }
	void SetPosG(Vector2 pos) { mGlobalPos.SetTranslate(pos.x, pos.y); }

	/* Rotation & Translation Functions*/
	void SetRot(float radians) { mLocalPos.SetRotateZ(radians); }
	void Translate(Vector2 pos) { mLocalPos.Translate(pos.x, pos.y); }
	void Rotate(float radians) { mLocalPos.RotateZ(radians); }
};