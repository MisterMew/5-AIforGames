#include "BehaviourPursue.h"
#include "PathFinding.h"
#include "raymath.h"
#include "Agent.h"
#include <map>

extern PathFind pafi;
extern GridMap gridMap;

map<Agent*, vector<Node*>> mPath = { };

void Pursue::SetTargetPos(Agent* agent, Vector2 pos) { 
	mTargetPos = pos; 

	Node* startNode = gridMap.AlignVectorToGrid(agent->GetPos());
	Node* endNode = gridMap.AlignVectorToGrid(pos);

	mPath[agent] = pafi.FindPath(startNode, endNode);
}

void Pursue::Update(Agent* agent, float deltaTime) {
	if (mPath.find(agent) == mPath.end() && mPath[agent].size() > 0) { return; } //No path found, return

	Node* node = mPath[agent][0];

	Vector2 originalDistance = Vector2Subtract(mPath[agent][0]->GetPos(), agent->GetPos()); // Calculate the distance between the target and the agents position
	//Vector2 pursueTarget = Vector2Add(GetTargetVel(), mPath[agent][0]->GetPos());			// New target to seek to based on the targets velocity and the prediction amount
	//Vector2 distance = Vector2Subtract(pursueTarget, agent->GetPos());		   // Get the distance between the target position and our position
	Vector2 normal = Vector2Normalize(originalDistance);							  // Normalize the direction
	
	Vector2 force = Vector2Subtract(Vector2Scale(normal, agent->GetMaxSpeed()), agent->GetVel()); // Calculate the force that will be added this frame
	force = Vector2Scale(Vector2Normalize(force), agent->GetMaxForce());						 // Make sure its within the specified bounds
	
	agent->SetForce(Vector2Add(force, agent->GetForce()));									   // Add the force to the acceleration
}
