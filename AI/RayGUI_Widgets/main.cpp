#pragma once

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#define RAYGUI_STATIC

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "raylib.h"
#include "raygui.h"
#include "raymath.h"

#include "CustomColours.h"
#include "PathFinding.h"
#include "GridMap.h"

using namespace std;
using std::vector;

GridMap gridMap;
PathFind pathFind;

#undef RAYGUI_IMPLEMENTATION

// / / / / / / / / / / | | | \ \ \ \ \ \ \ \ \ \ \\

#pragma region [ VARIABLES ]

//Main Variables
const int screenWidth = 1280;
const int screenHeight = 720;
float deltaTime = 0;
Vector2 mousePos;

Camera2D camera;
vector<Node*> foundPath;

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
	deltaTime = 0;

	camera = Camera2D();
	camera.zoom = 1.0f;			  // Multiplier
	camera.target = { 0, 0 };	 //
	camera.offset = { 10, 10 }; // Offset from target, shifts entire view
	camera.rotation = 0.0f;    // Nauseating beyblade effect xD 

	// Create Nodes //
	gridMap.CreateGridNetwork();
	gridMap.CreateConnections();

}

 /// UPDATE FUNCTION
/* Function to update the program while running */
void Update() {
	deltaTime = GetFrameTime();		//Get the frame rate
	mousePos = GetMousePosition(); //Get the mouse coordinates

	// Temp Code //
	   Vector2 temp = gridMap.MouseToGrid(mousePos);
	   Node* startNode = gridMap.map[0][0];
	   foundPath = pathFind.FindPath(startNode, gridMap.map[(int)temp.y][(int)temp.x]);
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


	// UI Details //
	DrawRectangleGradientV(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.3f), Fade(DIRTYGREY, 0.005f)); //Vignette
	DrawText(TextFormat("X, Y: [ %i, %i ]", (int)mousePos.x, (int)mousePos.y), 10, 28, 12, RAYWHITE);   //Draws the mouse coords in the top left corner
	DrawText(TextFormat("FPS: [ %i ]", (int)GetFPS()), 10, 10, 18, RAYWHITE);						   //Draws the FPS in the top left corner

	EndMode2D();
	EndDrawing();
}

 /// DEREFERENCING FUNCTION
/* Function to deference objects after use */
void DereferenceObjects() {}

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

// / / / / / / / / / / | | | \ \ \ \ \ \ \ \ \ \ \\