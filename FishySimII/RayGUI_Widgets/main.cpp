#pragma once

 /// CHECK LIST
// EntityObject.h .cpp checks out ~ no issues
// Behaviours.cpp remains empty, .h checks out

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

#include "Obstacle.h"
#include "EntityObject.h"
#include "Agent.h"
#include "AgentFish.h"

#include "BehaviourWander.h"
#include "BehaviourSeek.h"

#undef RAYGUI_IMPLEMENTATION

/// VARIABLES
const int screenWidth = 1280;
const int screenHeight = 720;
float deltaTime = 0;

//Toolbar:
int toolbarIndex = 1;
enum Toolbar { Null = 0, Slot1 = 1, Slot2, Slot3, Slot4, Slot5, Slot6, Slot7, Slot8, Slot9 };
const Vector2 toolSlot = { 115, 10 };
const float slotSize = 40;
const int toolbarSize = 9;

//Vector Lists:
static vector<EntityObject*> entities = {};
vector<Obstacle*> obstacles;
vector<Behaviour*> behaviours;

Vector2 target;
Agent* seeker;
Seek* seekBehaviour;
 

/// Function Declarations 
// Definitions below . . .
void ToolbarUpdate();
void ToolbarDraw();
void DrawTBSlot(int xPos, const char *text);

void DrawTarget();


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
	unsigned int obstacleAmount = rand() % 25;
	for (unsigned int i = 0; i <= obstacleAmount; i++) {
		obstacles.push_back(new Obstacle(Vector2{ (float)(rand() % screenWidth), (float)(rand() % screenHeight) }, (float)(rand() % 40)));
	}

	for (int i = 0; i < 100; i++) { 
		entities.push_back(new Fish({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) }));
	}

	// Create Seek behaviour //
	Agent* seeker = new Agent();
	Seek* seekBehaviour = new Seek();
	seekBehaviour->mTargetPosition;
	seeker->AddBehaviour(seekBehaviour);

	deltaTime = 0;
}

 /// UPDATE FUNCTION
/* Function to update the program while running */
void Update() {
	deltaTime = GetFrameTime();

	ToolbarUpdate();

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		DrawCircle(GetMouseX(), GetMouseY(), 15, Fade(BLACK, 0.5f));
	}

	for (unsigned int i = 0; i < entities.size(); i++) {
		entities[i]->Update(deltaTime);
	}

	if (seeker != nullptr) {
		seeker->Update(deltaTime);
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
}

 /// Main
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



#pragma region [ Private Functions ]

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

void ToolbarDraw() {
	float tempX = toolSlot.x;
	for (unsigned int i = 1; i <= toolbarSize; i++) {
		DrawRectangle(tempX, toolSlot.y, slotSize, slotSize, Color{ 10, 10, 10, 125 });
		DrawRectangleLinesEx({ tempX, toolSlot.y, slotSize, slotSize }, 3, BLACK);
		tempX = (tempX + slotSize) + 5;
	}

	DrawText("O",   128, 21, 20, GRAY);
	DrawText("<F>", 166, 21, 20, GRAY);
	DrawText("<S>", 210, 21, 20, GRAY);
	DrawText("+S", 438, 21, 20, GRAY);
	DrawText("+F", 483, 21, 20, GRAY);

	Vector2 mousePos = GetMousePosition(); //Get the mouse coordinates
	switch (toolbarIndex) {
	case Slot1: 
		DrawTBSlot(0, "Spawn an obstacle.");
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			obstacles.push_back(new Obstacle(Vector2{ mousePos.x, mousePos.y }, (float)(rand() % 40)));
		}
		break;
	case Slot2:
		DrawTBSlot(45, "Spawn a fish entity.");
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			entities.push_back(new Fish({ mousePos.x, mousePos.y }));
		}
		break;
	case Slot3:
		DrawTBSlot(90, "Spawns a shark entity. (Not Implemented)");
		break;
	case Slot4:
		DrawTBSlot(135, nullptr);
		break;
	case Slot5:
		DrawTBSlot(180, nullptr);
		break;
	case Slot6:
		DrawTBSlot(225, nullptr);
		break;
	case Slot7:
		DrawTBSlot(270, nullptr);
		break;
	case Slot8:
		DrawTBSlot(315, "Cause nearby entities to seek. (Not Implemented)");
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			DrawTarget();
			seekBehaviour->mTargetPosition = &mousePos;
		}
		break;
	case Slot9:
		DrawTBSlot(360, "Cause nearby entities to flee. (Not Implemented)");
		break;
	default: break;
	}
}

void DrawTBSlot(int xPos, const char *text) {
	DrawRectangleLines(toolSlot.x + xPos, toolSlot.y, slotSize, slotSize, WHITE);
	DrawText(text, 525, 22, 16, DARKGRAY);
}

#pragma endregion

void DrawTarget() {
	DrawLine(target.x - 5, target.y, target.x + 5, target.y, BLUE);
	DrawLine(target.x, target.y - 5, target.x, target.y + 5, BLUE);
}