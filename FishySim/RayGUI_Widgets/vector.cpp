#include "vector.h"

void Vector::Set(float x, float y) {
	mX = x;
	mY = y;
}

 /// ADDITION
/* Vector + Vector */
void Vector::AddVector(Vector& vector) {
	mX += vector.mX;
	mY += vector.mY;
}

/* Vector + Scalar */
void Vector::AddScalar(float scalar) {
	mX += scalar;
	mY += scalar;
}


 /// SUBTRACTION
/* Vector - Vector */
void Vector::SubVector(Vector& vector) {
	mX -= vector.mX;
	mY -= vector.mY;
}

/* Vector - Scalar */
void Vector::SubScalar(float scalar) {
	mX -= scalar;
	mY -= scalar;
}


 /// MULTIPLICATION
/* Vector * Vector */
void Vector::MultiplyVector(Vector& vector) {
	mX *= vector.mX;
	mY *= vector.mY;
}

/* Vector * Scalar */
void Vector::MultiplyScalar(float scalar) {
	mX *= scalar;
	mY *= scalar;
}


 /// DIVISION
/* Vector / Vector */
void Vector::DivideVector(Vector& vector) {
	mX /= vector.mX;
	mY /= vector.mY;
}

/* Vector / Scalar */
void Vector::DivideScalar(float scalar) {
	mX /= scalar;
	mY /= scalar;
}

/* Limit a value from exceeding its maximum */
void Vector::Limit(double max) {
	double limit = Magnitude();

	if (limit > max) {
		Set(mX / limit, mY / limit);
	}
}

/// Calculation Functions
float Vector::Distance(Vector& v) {
	return sqrt(pow(mX - v.mX, 2) + pow(mY - v.mY, 2));
}

float Vector::Dot(Vector& v) {
	return (mX * v.mX + mY * v.mY);
}

float Vector::Magnitude() {
	return sqrt(mX * mX + mY * mY);
}

void Vector::SetMag(float x) {
	Normalize();
	MultiplyScalar(x);
}

void Vector::Normalize() {
	float mag = Magnitude();

	if (mag > 0) {
		Set(mX / mag, mY / mag);
	}
	else {
		Set(mX, mY);
	}
}