#pragma once
#include "EntityObject.h"
#include "Behaviour.h"
#include "BehaviourPursue.h"
#include "BehaviourWander.h"
#include "BehaviourFlee.h"
#include <iostream>
#include <vector>

enum class BehaviourState { Wandering, Fleeing, Pursuing };
extern vector<EntityObject*> entities;

class Behaviour;
class State {
private: /// Private Variables
	BehaviourState currentState;

	Pursue* pursue = new Pursue();
	Wander* wander = new Wander();
	Flee* flee = new Flee();

protected: /// Public Variables
	EntityType mEntityType = {};
	BehaviourState mStateType = {};
	vector<Behaviour*> behaviours;

public: /// Public Functions
	State() : currentState(BehaviourState::Wandering) {}
	virtual ~State() {}

	void UpdateEntity(Agent* agent);
	void UpdateState(Agent* agent);

	/* Get */
	inline BehaviourState GetState() { return mStateType; }
	inline void SetState(BehaviourState state) { mStateType = state; }

	bool CheckForPredator(Agent* agent);
	bool CheckForPrey(Agent* agent);
};