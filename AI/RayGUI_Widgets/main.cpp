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

#include "Dijkstras.h"
#include "GridMap.h"

using namespace std;
using			std::vector;
using namespace dijkstras;

GridMap gridMap;

#undef RAYGUI_IMPLEMENTATION

// / / / / / / / / / / | | | \ \ \ \ \ \ \ \ \ \ \\

#pragma region [ VARIABLES ]

//Main Variables
const int screenWidth = 1280;
const int screenHeight = 720;
float deltaTime = 0;
Vector2 mousePos;

//Custom Color Variables
Color DIRTYGRAY = { 35, 35, 35, 255 };
Color ORANGEa = {255, 166, 0, 50};

vector<Node*> nodes;

#pragma endregion

void FormConnections(Node* newNode, int h, int w);

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

	// Create Nodes //
	Vector2 pos = { 0, 0 };
	for (int h = 0; h < (gridMap.mapHeight); h++) {
		for (int w = 0; w < (gridMap.mapWidth); w++) {
			Node* newNode = new Node();
			newNode->position = Vector2{ pos.x, pos.y };
			gridMap.map[h][w] = newNode;

			pos.x += 20;
		}
		pos.x = 0;
		pos.y += 20;
	}
	for (int h = 0; h < (gridMap.mapHeight); h++) {
		for (int w = 0; w < (gridMap.mapWidth); w++) {
			Node* newNode = new Node();
			FormConnections(newNode, h, w);
		}
	}

	//vector<Node*> shortestPath = DijkstrasSearch(nodes[100], nodes[2000]);
	//for (Node* node : shortestPath) {
	//	cout << node->gScore << endl;
	//}
}

 /// UPDATE FUNCTION
/* Function to update the program while running */
void Update() {
	deltaTime = GetFrameTime();		//Get the frame rate
	mousePos = GetMousePosition(); //Get the mouse coordinates
}

 /// DRAW FUNCTION
/* Function to manage drawing to the window while running */
void Draw() {
	BeginDrawing();

	ClearBackground(DIRTYGRAY);

	// Map Drawing //
	gridMap.DrawGrid(ORANGEa);
	gridMap.DrawNodes(nodes);

	DrawLine(nodes[100]->position.x, nodes[100]->position.y, nodes[2000]->position.x, nodes[2000]->position.y, BLUE);
	
	// UI Details //
	DrawRectangleGradientV(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.3f), Fade(DIRTYGRAY, 0.005f)); //Vignette
	DrawText(TextFormat("X, Y: [ %i, %i ]", (int)mousePos.x, (int)mousePos.y), 10, 28, 12, RAYWHITE);			  //Draws the mouse coords in the top left corner
	DrawText(TextFormat("FPS: [ %i ]", (int)GetFPS()), 10, 10, 18, RAYWHITE);									 //Draws the FPS in the top left corner

	EndDrawing();
}

 /// DEREFERENCING FUNCTION
/* Function to deference objects after use */
void DereferenceObjects() { }

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

void FormConnections(Node* newNode, int h, int w) {
	if (h < gridMap.mapHeight - 1) {newNode->connections.push_back(Edge{ gridMap.map[h + 1][w] }); } 
	if (w < gridMap.mapWidth - 1) { newNode->connections.push_back(Edge{ gridMap.map[h][w + 1] }); }
	if (h > 0) { newNode->connections.push_back(Edge{ gridMap.map[h - 1][w] }); }
	if (w > 0) { newNode->connections.push_back(Edge{ gridMap.map[h][w - 1] }); }
}
