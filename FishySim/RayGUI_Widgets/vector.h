#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Vector {
public:
	/// Variable Declarations
	float mX;
	float mY;

	/// Constructors
	Vector() {}
	Vector(float x, float y) { mX = x; mY = y; }

	/// Function Declarations
	/* Set function */
	void Set(float x, float y);

	/* Operation functions */
	void AddVector(Vector& v);
	void AddScalar(float s);

	void SubVector(Vector& v);
	void SubScalar(float s);

	void MultiplyVector(Vector& v);
	void MultiplyScalar(float s);

	void DivideVector(Vector& v);
	void DivideScalar(float s);

	/* Calculation Functions */
	void Limit(double limit);
	float Distance(Vector& v);
	float Dot(Vector& v);
	float Magnitude();
	void SetMag(float x);
	void Normalize();
};