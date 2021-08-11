#include "Agent.h"

Agent::Agent() : Agent({0, 0}) {}
Agent::Agent(Vector2 pos) { Init(pos); }
Agent::~Agent() {}

// Update the agent and its behaviours
void Agent::Update(float deltaTime) {
	//Flock();

	Vector2 pos = GetPos();
	Vector2 vel = GetVel();
	Vector2 acc = GetAcc();

	SetForce({0, 0});

	/* UPDATE all behaviours */
	for (auto behavior : mBehaviours){
		behavior->Update(*this, deltaTime);
	}

	// Change velocity and position based on motion/acceleration
	vel.x += acc.x * deltaTime; // * deltaTime to smooth no matter framerate
	vel.y += acc.y * deltaTime; // * deltaTime to smooth no matter framerate
	SetVel(Vector2Clamp(vel, -GetMaxSpeed(), GetMaxSpeed()));
	SetAcc({ 0, 0 });

	pos.x += vel.x;
	pos.y += vel.y;

	WrapScreenBounds(&pos); // Changed this to reference 'pos', so that it modifies the value
	SetPos(pos);
}

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
	SetAcc({ (float)(rand() % 2 + 1), (float)(rand() % 2 + 1) }); //Set the acceleration's X, Y value

	SetMaxSpeed(2.0f);
	SetMaxForce(0.5f);

	SetRotation(0);
	SetRotDampening(0.15f);
}

 /// COLLISION
/* Avoids collision with every other entity */
void Agent::AvoidEntities() {
	for (auto agent : *mAgents) {
		if (agent != this) {
			Vector2 d(Vector2Subtract(agent->GetPos(), GetPos()));
			float distanceSquared = Vector2Magnitude(d);

			float radius = 50;
			float radiusSquared = radius * radius;

			if (distanceSquared < radiusSquared && distanceSquared != 0) {
				float distance = sqrt(distanceSquared);
				Vector2 collisionNormal = Vector2Scale(d, 1.0f / distance);
				SetPos(Vector2Subtract(GetPos(), collisionNormal));
				agent->GetPos() = Vector2Add(agent->GetPos(), collisionNormal);
			}
		}
	}
}

 /// SCREEN WRAP
/* Allows agents to wrap around the screen */
void Agent::WrapScreenBounds(Vector2* pos) { 
	if (pos->x < 0) { pos->x = (float)GetScreenWidth(); }
	if (pos->y < 0) { pos->y = (float)GetScreenHeight(); }
	if (pos->x > (float)GetScreenWidth())  { pos->x = 0; }
	if (pos->y > (float)GetScreenHeight()) { pos->y = 0; }
}

#pragma endregion
