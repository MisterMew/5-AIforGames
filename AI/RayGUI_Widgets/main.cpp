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

#include "PathFinding.h"
#include "GridMap.h"

using namespace std;
using std::vector;

GridMap gridMap;
PathFind pafi;

#undef RAYGUI_IMPLEMENTATION

// / / / / / / / / / / | | | \ \ \ \ \ \ \ \ \ \ \\

#pragma region [ VARIABLES ]

//Main Variables
const int screenWidth = 1280;
const int screenHeight = 720;
float deltaTime = 0;
Vector2 mousePos;

//Custom Color Variables
Color DIRTYGREY = { 35, 35, 35, 255 };
Color LIGHTGREY = { 45, 45, 45, 255 };
Color ORANGEa = {255, 166, 0, 55};

vector<Node*> shortestPath;

#pragma endregion
#pragma region [ Other Functions ]

void FormConnections(Node* newNode, int h, int w);

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

	// Create Nodes //
	Vector2 pos = { 0, 0 };
	for (int h = 0; h < (gridMap.mapHeight); h++) {
		for (int w = 0; w < (gridMap.mapWidth); w++) {
			Node* newNode = new Node(pos, h, w);					 //Create a new Node
			newNode->mPosition = Vector2{ pos.x, pos.y };//Set its position on the screen
			gridMap.map[h][w] = newNode;			   //Set the map element to the node
	
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
	
	shortestPath = pafi.FindPath(gridMap.map[3][3], gridMap.map[30][40]);

	for (Node* node : shortestPath) {
		std::cout << node->GetGScore() << std::endl;
	}
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

	ClearBackground(DIRTYGREY);

	// Map Drawing //
	gridMap.DrawGrid(LIGHTGREY);
	gridMap.DrawIntersects(LIGHTGREY);

	gridMap.DrawNodes(ORANGEa);

	//Draw the graph
	vector<Node*>* drawnList = new vector<Node*>();
	pafi.DrawGraph(gridMap.map[3][3], drawnList);
	delete drawnList;

	//Draw the shortest path
	for (Node* node : shortestPath) {
		gridMap.DrawNode(node, true);
	}

	// UI Details //
	DrawRectangleGradientV(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.3f), Fade(DIRTYGREY, 0.005f)); //Vignette
	DrawText(TextFormat("X, Y: [ %i, %i ]", (int)mousePos.x, (int)mousePos.y), 10, 28, 12, RAYWHITE);   //Draws the mouse coords in the top left corner
	DrawText(TextFormat("FPS: [ %i ]", (int)GetFPS()), 10, 10, 18, RAYWHITE);						   //Draws the FPS in the top left corner

	EndDrawing();
}

 /// DEREFERENCING FUNCTION
/* Function to deference objects after use */
void DereferenceObjects() {
	//for (int h = 0; h < (gridMap.mapHeight); h++) {
	//	for (int w = 0; w < (gridMap.mapWidth); w++) {
	//		delete gridMap.map[h][w];
	//	}
	//}
	//delete gridMap.map;
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

// / / / / / / / / / / | | | \ \ \ \ \ \ \ \ \ \ \\

void FormConnections(Node* newNode, int h, int w) {
	const float cost = 1;
	if (h < gridMap.mapHeight - 1) {newNode->connections.push_back(Edge{ gridMap.map[h + 1][w], cost }); }
	if (w < gridMap.mapWidth - 1) { newNode->connections.push_back(Edge{ gridMap.map[h][w + 1], cost }); }
	if (h > 0) { newNode->connections.push_back(Edge{ gridMap.map[h - 1][w], cost }); }
	if (w > 0) { newNode->connections.push_back(Edge{ gridMap.map[h][w - 1], cost }); }
}
