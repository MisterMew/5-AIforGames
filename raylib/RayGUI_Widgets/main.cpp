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

#undef RAYGUI_IMPLEMENTATION

/// VARIABLES
const int screenWidth = 1280;
const int screenHeight = 720;
float deltaTime = 0;

int toolbarIndex = 1;
enum Toolbar { Null = 0, Slot1 = 1, Slot2, Slot3, Slot4, Slot5, Slot6, Slot7, Slot8, Slot9 };

vector<Obstacle*> obstacles;
vector<Behaviour*> behaviours;
static vector<EntityObject*> entities = {};
 
/// Function Declarations 
// Definitions below . . .
void ToolbarUpdate();
void ToolbarDraw();


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

	for (int i = 0; i < 10; i++) { entities.push_back(new Fish({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) })); }

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

	/* Delete Obstacles */
	for (unsigned int i = 0; i < obstacles.size(); i++) {
		delete obstacles[i];
	}
	obstacles.clear();
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
			toolbarIndex = 1;
		}
	}
	else if (mouseScroll < 0) {
		toolbarIndex++;
		if (toolbarIndex > sizeof(Toolbar)) {
			toolbarIndex = sizeof(Toolbar);
		}
	}
}

void ToolbarDraw() {
	const Vector2 toolSlot = { 115, 10 };
	const float slotSize = 40;

	float tempX = toolSlot.x;
	for (unsigned int i = 1; i <= sizeof(Toolbar); i++) {
		DrawRectangle(tempX, toolSlot.y, slotSize, slotSize, Color{ 10, 10, 10, 125 });
		DrawRectangleLinesEx({ tempX, toolSlot.y, slotSize, slotSize }, 3, BLACK);
		tempX = (tempX + slotSize) + 5;
	}

	switch (toolbarIndex) {
	case Slot1: 
		DrawRectangleLines(toolSlot.x, toolSlot.y, slotSize, slotSize, WHITE);
		break;
	case Slot2: 
		DrawRectangleLines(toolSlot.x + 45, toolSlot.y, slotSize, slotSize, WHITE);
		break;
	case Slot3:
		DrawRectangleLines(toolSlot.x + 90, toolSlot.y, slotSize, slotSize, WHITE); 
		break;
	case Slot4:
		DrawRectangleLines(toolSlot.x + 135, toolSlot.y, slotSize, slotSize, WHITE); 
		break;
	case Slot5:
		DrawRectangleLines(toolSlot.x + 180, toolSlot.y, slotSize, slotSize, WHITE);
		break;
	default: break;
	}
}

#pragma endregion