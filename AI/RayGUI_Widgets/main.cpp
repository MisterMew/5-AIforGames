#pragma once

/* TO DO:
* Create objects
* Create State Machine
*/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#define RAYGUI_STATIC

#include "raylib.h"
#include "raygui.h"
#include "raymath.h"

#include "EntityObject.h"
#include "Agent.h"
#include "AgentPrey.h"
#include "AgentPredator.h"
#include "EntityObstacle.h"

#include "CustomColours.h"
#include "PathFinding.h"
#include "GridMap.h"

#undef RAYGUI_IMPLEMENTATION

GridMap gridMap;
PathFind pathFind;

// / / / / / / / / / / | | | \ \ \ \ \ \ \ \ \ \ \\

#pragma region [ VARIABLES ]

//Main Variables
const int screenWidth = 1280;
const int screenHeight = 720;
float deltaTime = 0;
Vector2 mousePos;

Camera2D camera;

//Vector Lists:
vector<EntityObject*> agents = {};
vector<Behaviour*> behaviours;
vector<Obstacle*> obstacles;
vector<Node*> foundPath;

#pragma endregion
#pragma region [ Function Declarations ]

 /// Function Declarations 
// Definitions below . . .
void SetupCamera();
void SpawnEntitiesPrey(unsigned int amount);
void SpawnEntitiesPred(unsigned int amount);
void SpawnObstacles(unsigned int amount);

#pragma endregion
#pragma region [ Main Program Functions ]

 /// INITIALISATION
/* Program initialisation */
void Init() {
	InitWindow(screenWidth, screenHeight, "AI Project"); //Initialise raylib window dimensions and change title
	SetTargetFPS(60);								    //Set the target FPS

	SetExitKey(0);
}

 /// START FUNCTION
/* Function to handle the events before running the program (setup) */
void Start() {
	SetupCamera();

	// Spawn Entities //
	///SpawnEntitiesPrey(10);
	///SpawnEntitiesPred(1);
	SpawnObstacles(20);

	// Create Nodes //
	gridMap.CreateGridNetwork();
	gridMap.CreateConnections();

	deltaTime = 0;
}

 /// UPDATE FUNCTION
/* Function to update the program while running */
void Update() {
	deltaTime = GetFrameTime();		//Get the frame rate
	mousePos = GetMousePosition(); //Get the mouse coordinates

	// Update Entities //
	for (auto entity : agents) { entity->Update(deltaTime); }

	// Temp Code //
	   Node* startNode = gridMap.map[0][0];
	   foundPath = pathFind.FindPath(startNode, gridMap.AlignVectorToGrid(mousePos));
	// ==== ==== //
}

 /// DRAW FUNCTION
/* Function to manage drawing to the window while running */
void Draw() {
	BeginDrawing();
	BeginMode2D(camera);
	ClearBackground(DIRTYGREY);

	// Map Drawing //
	gridMap.DrawGrid(LIGHTGREY);
	gridMap.DrawIntersects(LIGHTGREY);

	gridMap.DrawNodes(ORANGEa);
	gridMap.DrawPath(foundPath);

	// Draw Entities & Objects //
	for (auto obstacle : obstacles) { obstacle->Draw(); }
	for (auto entity : agents) { entity->Draw(); }

	// UI Details //
	DrawRectangleGradientV(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.3f), Fade(DIRTYGREY, 0.005f)); //Vignette
	DrawText(TextFormat("X, Y: [ %i, %i ]", (int)mousePos.x, (int)mousePos.y), 10, 28, 12, RAYWHITE);   //Draws the mouse coords in the top left corner
	DrawText(TextFormat("FPS: [ %i ]", (int)GetFPS()), 10, 10, 18, RAYWHITE);						   //Draws the FPS in the top left corner

	EndMode2D();
	EndDrawing();
}

 /// DEREFERENCING FUNCTION
/* Function to deference objects after use */
void DereferenceObjects() {
	/* Delete Entities */
	for (unsigned int i = 0; i < agents.size(); i++) {
		delete agents[i];
	}
	agents.clear();

	/* Delete Obstacles */
	for (unsigned int i = 0; i < obstacles.size(); i++) {
		delete obstacles[i];
	}
	obstacles.clear();
}

/// Main ///
int main() {
	Init();
	Start();

	bool exitWindow = false;
	while (!exitWindow) {
		exitWindow = WindowShouldClose();

		Update();
		Draw();
	}

	DereferenceObjects();
	CloseWindow();
}

#pragma endregion

// / / / / / / / / / / | | | \ \ \ \ \ \ \ \ \ \ \\

 /// CAMERA REPOSITION
/* Reposition the raylib camera to center the graph */
void SetupCamera() {
	camera = Camera2D();
	camera.zoom = 1.0f;			  // Multiplier
	camera.target = { 0, 0 };	 //
	camera.offset = { 10, 10 }; // Offset from target, shifts entire view
	camera.rotation = 0.0f;    // Nauseating beyblade effect xD 
}

 /// SPAWN: Prey
/* Spawn the prey entities */
void SpawnEntitiesPrey(unsigned int amount) {
	for (int i = 0; i < amount; i++) {
		agents.push_back(new Prey({ (float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) }));
	}
}

 /// SPAWN: Predator
/* Spawn the predator entities */
void SpawnEntitiesPred(unsigned int amount) {
	for (int i = 0; i < amount; i++) {
		agents.push_back(new Predator({ (float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) }));
	}
}

 /// SPAWN: Obstacles
/* Spawn the obstacle entities */
void SpawnObstacles(unsigned int amount) {
	for (int i = 0; i < amount; i++) {
		//obstacles.push_back(new Obstacle(gridMap.AlignPositionToGrid({ (float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) })));
	}
}