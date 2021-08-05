#pragma once

#include <iostream>
#include <string>

using namespace std;

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#define RAYGUI_STATIC

#include "raylib.h"
#include "raygui.h"
#include "FleeBehaviour.h"
#include "SeekBehaviour.h"
#include "WanderBehaviour.h"

#undef RAYGUI_IMPLEMENTATION

/// VARIABLES
const int screenWidth = 1280;
const int screenHeight = 720;

 /// INITIALISATION
/* Program initialisation */
void Init() {
	InitWindow(screenWidth, screenHeight, "Made with Raylib"); //Initialise raylib window dimensions and change title
	SetTargetFPS(60); //Set the target FPS

	SetExitKey(0);
}

void Update() {}

void Draw() {
	BeginDrawing();
	ClearBackground({ 23, 23, 23 });
	DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(DARKBLUE, 0.3f), Fade(BLUE, 0.005f));

	Vector2 mousePos = GetMousePosition(); //Get the mouse coordinates
	DrawRectangleGradientV(0, 0, GetScreenWidth(), (GetScreenHeight() / 8), Fade(BLACK, 0.3f), Fade(DARKBLUE, 0.005f));
	DrawText(TextFormat("X, Y: [ %i, %i ]", (int)mousePos.x, (int)mousePos.y), 10, 28, 12, RAYWHITE); //Draws the mouse coords in the top left corner
	DrawText(TextFormat("FPS: [ %i ]", (int)GetFPS()), 10, 10, 18, RAYWHITE);						 //Draws the FPS in the top left corner

	EndDrawing();
}

 /// Main
int main() {
	Init(); //Initialisation

	float deltaTime = 0;

	bool exitWindow = false;
	while (!exitWindow) {
		exitWindow = WindowShouldClose();
		
		Update();
		Draw();
	}

	CloseWindow();
}