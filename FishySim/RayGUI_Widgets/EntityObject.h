#pragma once
#include "Vector2.h"
#include "Matrix3.h"
#include <vector>
#include <iostream>

using namespace std;

class EntityObject {
	EntityObject* entity = nullptr;
	vector<EntityObject> entityChild;
	
	/// Entity Variables
	Matrix3 mLocalPos;
	Matrix3 mGlobalPos;

public:
	EntityObject();
	~EntityObject();

	/// Function Definitions
	Matrix3 GetPosL() { return mLocalPos; }
	Matrix3 GetPosG() { return mGlobalPos; }

	void SetPosL(Vector2 pos) { mLocalPos.SetTranslate(pos.x, pos.y); }
	void SetPosG(Vector2 pos) { mGlobalPos.SetTranslate(pos.x, pos.y); }
	void SetRot(float radians) { mLocalPos.SetRotateZ(radians); }

	void Translate(Vector2 pos) { mLocalPos.Translate(pos.x, pos.y); }
	void Rotate(float radians) { mLocalPos.RotateZ(radians); }

	/// Function Declarations
	void UpdatePosition();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};