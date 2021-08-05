#pragma once
#include "Behaviour.h"

class WanderBehaviour : public Behaviour {
private:
	/// Variables:
	float m_circleDistance = 10;
	float m_circleRadius = 150;
	float m_wanderAngle = 0;

	const float m_angleChange = 100;

	/// DEBUG ONLY
	Vector2 debug_cirleCenter;
	Vector2 debug_displacement;
	/// DEBUG ONLY

	/// Function Declaration:
	Vector2 SetAngle(Vector2 vector, float value);

public:
	WanderBehaviour();
	virtual ~WanderBehaviour() {};

	virtual bool Update(Agent* agent, float deltaTime);
	void Draw(Agent* agent);
};

