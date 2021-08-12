#pragma once
#include "EntityObject.h"
#include "raymath.h"
#include "Agent.h"

class FlockBehaviour {
private:
	/* Boid Variables */
	float mSeperation;
	float mAlignment;
	float mCohesion;

public:
	FlockBehaviour();
	virtual ~FlockBehaviour();

	void Flock(Agent* agent, float sepCoef, float aliCoef, float cohCoef);

	Vector2 Seperate(Agent* agent);
	Vector2 Align(Agent* agent);
	Vector2 Cohese(Agent* agent);

	float GetSeperation() { return mSeperation; }
	float GetAlignment() { return mAlignment; }
	float GetCohesion() { return mCohesion; }

	void SetSeperation(float sep) { mSeperation = sep; }
	void SetAlignment(float ali) { mAlignment = ali; }
	void SetCohesion(float coh) { mCohesion = coh; }
};