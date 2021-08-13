#pragma once

 /// CHECK LIST
// EntityObject.h .cpp checks out ~ no issues
// Behaviours.cpp remains empty, .h checks out

/* What To Do;
* Seeking, Fleeing, Wander, Flocking, Avoid
* 
* Flocking:
*	Cannot find where/why flocking wont function
* 
* Avoid:
*	Need to attempt avoiding again (entities currently ignore all obstacles)
*	Whatever is in the agent.cpp doesn't do anything to aid avoiding, felt cute, might delete later
* 
* ;3 mew
* 
*/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_COLORS
#define RAYGUI_SUPPORT_ICONS
#define RAYGUI_STATIC

#include "raylib.h"
#include "raygui.h"

#include "EntityObject.h"
#include "Obstacle.h"
#include "Agent.h"
#include "AgentFish.h"

#include "BehaviourSeek.h"
#include "BehaviourFlee.h"
#include "BehaviourAvoid.h"

#undef RAYGUI_IMPLEMENTATION

// / / / / / / / / / / | | | \ \ \ \ \ \ \ \ \ \ \\

#pragma region [ VARIABLES ]

//Main Variables
const int screenWidth = 1280;
const int screenHeight = 720;
float deltaTime = 0;
Vector2 mouseXY;

//Toolbar:
int toolbarIndex = 1;
enum Toolbar { Null = 0, Slot1 = 1, Slot2, Slot3, Slot4, Slot5, Slot6, Slot7, Slot8, Slot9 };
const Vector2 toolSlot = { 115, 10 };
const float slotSize = 40;
const int toolbarSize = 9;

//Vector Lists:
vector<EntityObject*> entities = {};
vector<Obstacle*> obstacles;
vector<Behaviour*> behaviours;

//Behaviours:
int behaviourIndex; // seek = 1, flee = 2 //
SeekBehaviour* seekBehaviour;
FleeBehaviour* fleeBehaviour;
AvoidBehaviour* avoidBehaviour;

#pragma endregion
#pragma region [ Function Declarations ]

 /// Function Declarations 
// Definitions below . . .
void ToolbarUpdate();
void ToolbarDraw();
void DrawTBSlot(int xPos, const char *text);
void DrawTarget();

void ValidateBehaviour(Behaviour* behaviour, int index);
void InsertBehaviour(Behaviour* behaviour);
void RemoveBehaviours();

#pragma endregion
#pragma region [ Main Program Functions ]

 /// INITIALISATION
/* Program initialisation */
void Init() {
	InitWindow(screenWidth, screenHeight, "Sofishticated Sea++ Program II"); //Initialise raylib window dimensions and change title
	SetTargetFPS(60); //Set the target FPS

	SetExitKey(0);
}

 /// START FUNCTION
/* Function to handle the events before running the program (setup) */
void Start() {
	seekBehaviour = new SeekBehaviour();
	fleeBehaviour = new FleeBehaviour();
	avoidBehaviour = new AvoidBehaviour();
	seekBehaviour->SetTargetPosition(&mouseXY);
	fleeBehaviour->SetTargetPosition(&mouseXY);
	avoidBehaviour->SetTargetPosition(&mouseXY);

	unsigned int obstacleAmount = rand() % 25;
	for (unsigned int i = 0; i <= obstacleAmount; i++) {
		obstacles.push_back(new Obstacle(Vector2{ (float)(rand() % screenWidth), (float)(rand() % screenHeight) }, (float)(rand() % 40)));
	}

	for (int i = 0; i < 100; i++) { 
		entities.push_back(new Fish({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) }));
		InsertBehaviour(avoidBehaviour);
	}

	deltaTime = 0;
}

 /// UPDATE FUNCTION
/* Function to update the program while running */
void Update() {
	deltaTime = GetFrameTime();

	ToolbarUpdate();

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		mouseXY = GetMousePosition();
		DrawCircle(mouseXY.x, mouseXY.y, 15, Fade(BLACK, 0.5f));
	}

	for (unsigned int i = 0; i < entities.size(); i++) {
		entities[i]->Update(deltaTime);
	}
}

 /// DRAW FUNCTION
/* Function to manage drawing to the window while running */
void Draw() {
	BeginDrawing();
	ClearBackground({ 13, 13, 13 });
	DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLUE, 0.3f), Fade(SKYBLUE, 0.005f));

	for (auto obstacle : obstacles) { //Draw the obstacles as circles
		DrawCircle(obstacle->mPosition.x, obstacle->mPosition.y, obstacle->mRadius, Color{ 23, 23, 23, 200 });
	}

	for (auto entity : entities) {
		entity->Draw();
	}

	Vector2 mousePos = GetMousePosition(); //Get the mouse coordinates
	DrawRectangleGradientV(0, 0, GetScreenWidth(), (GetScreenHeight() / 10), Fade(BLACK, 0.3f), Fade(DARKBLUE, 0.005f));
	DrawText(TextFormat("X, Y: [ %i, %i ]", (int)mousePos.x, (int)mousePos.y), 10, 28, 12, RAYWHITE); //Draws the mouse coords in the top left corner
	DrawText(TextFormat("FPS: [ %i ]", (int)GetFPS()), 10, 10, 18, RAYWHITE);						 //Draws the FPS in the top left corner
	ToolbarDraw();

	EndDrawing();
}

 /// DEREFERENCING FUNCTION
/* Function to deference objects after use */
void DereferenceObjects() {
	/* Delete Entities */
	for (unsigned int i = 0; i < entities.size(); i++) {
		delete entities[i];
	}
	entities.clear();

	/* Delete Behaviours */
	for (unsigned int i = 0; i < behaviours.size(); i++) {
		delete behaviours[i];
	}
	behaviours.clear();

	/* Delete Obstacles */
	for (unsigned int i = 0; i < obstacles.size(); i++) {
		delete obstacles[i];
	}
	obstacles.clear();

	delete seekBehaviour;
	delete fleeBehaviour;
	delete avoidBehaviour;
}

 /// Main ///
int main() {
	Init(); //Initialisation
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
#pragma region [ PRIVATE FUNCTIONS ]

 /// TOOLBAR: Update
/* Updates the toolbar */
void ToolbarUpdate() {
	int mouseScroll = GetMouseWheelMove();

	if (mouseScroll > 0) {
		toolbarIndex--;
		if (toolbarIndex < 1) {
			toolbarIndex = toolbarSize;
		}
	}
	else if (mouseScroll < 0) {
		toolbarIndex++;
		if (toolbarIndex > toolbarSize) {
			toolbarIndex = 1;
		}
	}
}

/// TOOLBAR: Draw
/* Draw everything to do with the toolbar */
void ToolbarDraw() {
	///Dynamically draw the toolbar
	float tempX = toolSlot.x;
	for (unsigned int i = 1; i <= toolbarSize; i++) {
		DrawRectangle(tempX, toolSlot.y, slotSize, slotSize, Color{ 10, 10, 10, 125 });
		DrawRectangleLinesEx({ tempX, toolSlot.y, slotSize, slotSize }, 3, BLACK);
		tempX = (tempX + slotSize) + 5;
	}

	///Label the toolbar
	Color TEXTCOLOR = GRAY;
	DrawText("O",   128, 21, 20, TEXTCOLOR);
	DrawText("<F>", 166, 21, 20, TEXTCOLOR);
	DrawText("<S>", 210, 21, 20, DARKGRAY);
	DrawText("+S", 438, 21, 20, TEXTCOLOR);
	DrawText("+F", 483, 21, 20, TEXTCOLOR);

	///For each slot of the toolbar
	Vector2 mousePos = GetMousePosition(); //Get the mouse coordinates
	switch (toolbarIndex) {
	case Slot1: // Create an Obstacle Object
		DrawTBSlot(0, "Spawn an obstacle.");
		RemoveBehaviours();
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			obstacles.push_back(new Obstacle(Vector2{ mousePos.x, mousePos.y }, (float)(rand() % 40)));
		}
		break;

	case Slot2: // Create a Fish Entity
		DrawTBSlot(45, "Spawn a fish entity.");
		RemoveBehaviours();
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			entities.push_back(new Fish({ mousePos.x, mousePos.y }));
		}
		break;

	case Slot3: // Create a Shark Entity
		DrawTBSlot(90, "Spawns a shark entity. (Not Implemented)");
		RemoveBehaviours();
		break;

	case Slot4:
		DrawTBSlot(135, nullptr);
		RemoveBehaviours();
		break;

	case Slot5:
		DrawTBSlot(180, nullptr);
		RemoveBehaviours();
		break;

	case Slot6:
		DrawTBSlot(225, nullptr);
		RemoveBehaviours();
		break;

	case Slot7:
		DrawTBSlot(270, nullptr);
		RemoveBehaviours();
		break;

	case Slot8: // Demonstrates Seeking AI
		DrawTBSlot(315, "Cause nearby entities to seek. (Not Implemented)");
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			seekBehaviour->SetTargetPosition(&mouseXY);
			ValidateBehaviour(seekBehaviour, 1);
		}
		DrawTarget();
		break;

	case Slot9: // Demonstrates Fleeing AI
		DrawTBSlot(360, "Cause nearby entities to flee. (Not Implemented)");
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			fleeBehaviour->SetTargetPosition(&mouseXY);
			ValidateBehaviour(fleeBehaviour, 2);
		}
		DrawTarget();
		break;

	default: break;
	}
}

/* This draws a single tool slot */
void DrawTBSlot(int xPos, const char *text) {
	DrawRectangleLines(toolSlot.x + xPos, toolSlot.y, slotSize, slotSize, WHITE);
	DrawText(text, 525, 22, 16, GRAY);
}

/* Draws the little crosshair target for fleeing/seeking */
void DrawTarget() {
	Color TARGETCOLOR = BLACK;
	if (behaviourIndex == 1) { TARGETCOLOR = DARKBLUE; }
	if (behaviourIndex == 2) { TARGETCOLOR = MAROON; }

	DrawLine(mouseXY.x - 5, mouseXY.y, mouseXY.x + 5, mouseXY.y, TARGETCOLOR);
	DrawLine(mouseXY.x, mouseXY.y - 5, mouseXY.x, mouseXY.y + 5, TARGETCOLOR);
}

#pragma region [ PRIVATE FUNCTIONS: BEHAVIOURS ]

void ValidateBehaviour(Behaviour* behaviour, int index) {
	if (behaviourIndex != index) {
		RemoveBehaviours();
		InsertBehaviour(behaviour);
		behaviourIndex = index;
	}
}

void InsertBehaviour(Behaviour* behaviour) {
	for (auto entity : entities) {
		Agent* agent = (Agent*)entity; //Cast entity to agent
		agent->AddBehaviour(behaviour);
	}
}

void RemoveBehaviours() {
	for (auto entity : entities) {
		Agent* agent = (Agent*)entity; //Cast entity to agent
		agent->ClearBehaviour();
	}
}

#pragma endregion
#pragma endregion [ PRIVATE FUNCTIONS ]