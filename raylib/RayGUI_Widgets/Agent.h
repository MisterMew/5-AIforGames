#pragma once
#include "EntityObject.h"
#include "Behaviour.h"
#include "raymath.h"
#include <vector>
#include <cmath>

class Behaviour;

class Agent : public EntityObject {
private:
	Vector2 Truncate(Vector2 v, float max);

protected:
	std::vector<Behaviour*> mBehaviourList;

public:
	Agent();
	Agent(Vector2 position);
	~Agent();

	void Update(float deltaTime) override;

	void AddBehaviour(Behaviour* behaviour);

	/* Vector Additions */
	Vector2 Truncate(Vector2 vector, float max);
	Vector2 Vector2Clamp(Vector2 vector, float clampMin, float clampMax);
	float Vector2Magnitude(Vector2 vector);
};


