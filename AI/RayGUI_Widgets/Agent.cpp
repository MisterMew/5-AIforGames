#include "Agent.h"

#pragma region [ Public Functions ]

 /// UPDATE
/* Update the agent and its behaviours */
void Agent::Update(float deltaTime) {
	SetForce({0, 0});

	state.UpdateEntity(this);

	SetVel(Vector2Truncate((Vector2Add(GetVel(), Vector2Scale(GetForce(), deltaTime))), GetMaxSpeed()));
	SetPos((Vector2Add(GetPos(), Vector2Scale(GetVel(), deltaTime))));

	SetVel(Vector2Scale(GetVel(), GetFriction()));
}

#pragma endregion
#pragma region [ Vector2 Math Operations ]

 /// VECTOR2: TRUNCATE
/* Truncates the given vector */
Vector2 Agent::Vector2Truncate(Vector2 vec, float max) {
	float i = max / Vector2Length(vec);
	i = i < 1.0F ? i : 1.0F;
	return Vector2Scale(vec, i);
}

 /// VECTOR2: Clamp
/* Clamp the given vector to be within a set range */
Vector2 Agent::Vector2Clamp(Vector2 vec, float min, float max) {
	if (vec.x < min) { vec.x = min; }
	if (vec.y < min) { vec.y = min; }
	if (vec.x > max) { vec.x = max; }
	if (vec.y > max) { vec.y = max; }

	return vec;
}

 /// VECTOR2: Magnitude
/* Return the magnitude of the given vector */
float Agent::Vector2Magnitude(Vector2 vec) {
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

#pragma endregion
#pragma region [ Private Functions ]

 /// INITIALISE CONSTRUCTOR
/* Called by the constructor to Initialise variables */
void Agent::Init(Vector2 pos) {
	EntityObject::SetPos(pos);

	SetVel({ rand() % (int)10.0F - 5.0F, rand() % (int)10.0F - 5.0F }); //Set the velocity's X, Y values
	SetAcc({ (float)(rand() % 2 + 1), (float)(rand() % 2 + 1) });	   //Set the acceleration's X, Y value

	SetMaxSpeed(5.0F);
	SetMaxForce(5.0F);
}

#pragma endregion