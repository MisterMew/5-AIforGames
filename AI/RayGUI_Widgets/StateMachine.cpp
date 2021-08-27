#include "StateMachine.h"
#include "Agent.h"

void State::UpdateEntity(Agent* agent) {
	BehaviourState desiredState = BehaviourState::Wandering;

	switch (agent->GetEntity()) {
	case EntityType::objPrey:
		if (CheckForPredator(agent)) { desiredState = BehaviourState::Fleeing; }
		break;

	case EntityType::objPredator:
		if (CheckForPrey(agent)) { desiredState = BehaviourState::Pursuing; }
		break;

	default: break;
	}

	if (currentState != desiredState) {
		agent->SetState(desiredState);
		UpdateState(agent);
		currentState = desiredState;
	}
}

void State::UpdateState(Agent* agent) {
	switch (mStateType) {
	
	case BehaviourState::Fleeing:
		agent->ClearBehaviour();
		agent->AddBehaviour(flee);
		cout << "!STATE CHANGED: Flee" << endl;
		break;
	
	case BehaviourState::Pursuing:
		agent->ClearBehaviour();
		agent->AddBehaviour(pursue);
		cout << "!STATE CHANGED: Pursue" << endl;
		break;
	
	default: /* Wander */
		agent->ClearBehaviour();
		agent->AddBehaviour(wander);
		cout << "!STATE CHANGED: Wandering" << endl;
		break;
	}
}

bool State::CheckForPredator(Agent* agent) { 
	for (auto ent : entities) {
		if (ent == agent) { continue; }
		if (ent->GetEntity() == EntityType::objPredator) {
			if (Vector2Distance(ent->GetPos(), agent->GetPos()) < 100) {
				flee->SetTargetPos(ent->GetPos());
				flee->Update(agent, GetFrameTime());
				return true;
			}
		}
	}
	return false; 
}

bool State::CheckForPrey(Agent* agent) {
	for (auto ent : entities) {
		if (ent == agent) { continue; }
		if (ent->GetEntity() == EntityType::objPrey) {
			if (Vector2Distance(ent->GetPos(), agent->GetPos()) < 100) {
				pursue->SetTargetPos(agent, ent->GetPos());
				pursue->Update(agent, GetFrameTime());
				return true;
			}
		}
	}
	return false;
}