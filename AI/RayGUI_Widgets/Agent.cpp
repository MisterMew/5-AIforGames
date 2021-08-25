#include "Agent.h"

Agent::Agent() : Agent({ 0, 0 }) {}
Agent::Agent(Vector2 pos) { Init(pos); }
Agent::~Agent() {}


#pragma region [ Public Functions ]

// Update the agent and its behaviours
void Agent::Update(float deltaTime) {
	Vector2 pos = GetPos();
	Vector2 vel = GetVel();

	SetForce({0, 0});

	// If (velocity + steering) equals zero, then there is no movement
	SetVel( Vector2Truncate((Vector2Add(vel, Vector2Scale(GetForce(), deltaTime))), GetMaxSpeed()) );
	SetPos( (Vector2Add(pos, Vector2Scale(vel, deltaTime))) );

	SetVel( Vector2Scale(vel, GetFriction()) );

	WrapScreenBounds(&pos);
	SetPos(pos);
}

#pragma endregion
#pragma region [ Vector2 Math Operations ]

 /// VECTOR2: TRUNCATE
/* Truncates the given vector */
Vector2 Agent::Vector2Truncate(Vector2 vec, float max) {
	float i = max / Vector2Length(vec);
	i = i < 1.0 ? i : 1.0;
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

	SetMaxSpeed(2.0f);
	SetMaxForce(0.5f);
}

 /// SCREEN WRAP
/* Allows agents to wrap around the screen */
void Agent::WrapScreenBounds(Vector2* pos) {
	if (pos->x < 0) { pos->x = (float)GetScreenWidth(); }
	if (pos->y < 0) { pos->y = (float)GetScreenHeight(); }
	if (pos->x > (float)GetScreenWidth()) { pos->x = 0; }
	if (pos->y > (float)GetScreenHeight()) { pos->y = 0; }
}

#pragma endregion