
/// TO DO:
// Prevent fish from boiding with other entities
// Give whales obstacle collision
// Make fish flee from sharks
// Make sharks hunt fish

#include <iostream>
#include <ctime>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#define RAYGUI_STATIC

#include "raylib.h"
#include "raygui.h"
#include "EntityObject.h"
#include "Agent.h"
#include "AgentFish.h"
#include "AgentShark.h"
#include "AgentWhale.h"

#undef RAYGUI_IMPLEMENTATION

/// Variables
const int screenWidth = 1280;  //Set screen width
const int screenHeight = 720; //Set screen height
<<<<<<< HEAD
float deltaTime = 0;
int spawnIndex = 0;

enum SpawnArray { Empty = 0, SpawnFish, SpawnShark, SpawnWhale };
vector<EntityObject*> entities = {};
=======

vector<EntityObject*> mEntity = {};

>>>>>>> parent of ebb9e7f (fixed~)

 /// INITIALISATION
/* Program initialisation */
void Init() {
	InitWindow(screenWidth, screenHeight, "Sofishticated Sea++ Program"); //Initialise raylib window dimensions and change title
	SetTargetFPS(60); //Set the target FPS

	SetExitKey(0);
}

 /// START
/* Starts the program before run */
void Start() {
	//for (int i = 0; i < 250; i++) { mEntity.push_back(new Fish({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) })); }
	for (int i = 0; i < 75; i++) { entities.push_back(new Shark({ (float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) })); }
}

 /// UPDATE
/* Updates program while running */
void Update() {
<<<<<<< HEAD
	int mouseMove = GetMouseWheelMove();
	if (mouseMove > 0) {
		spawnIndex--;
		if (spawnIndex < 0) {
			spawnIndex = 0; // Clamp
		}
	}
	else if (mouseMove < 0) {
		spawnIndex++;
		if (spawnIndex > sizeof(SpawnArray)) {
			spawnIndex = sizeof(SpawnArray) - 1; // Clamp
		}
	}

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		DrawCircle(GetMouseX(), GetMouseY(), 15, Fade(RAYWHITE, 0.1f));
	}
=======
>>>>>>> parent of ebb9e7f (fixed~)
}

 /// DRAWING
/* Program drawing while running */
void Draw() {
	BeginDrawing();
	ClearBackground({ 23, 23, 23 });
	DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(DARKBLUE, 0.3f), Fade(BLUE, 0.005f));
	DrawRectangleGradientV(0, 0, GetScreenWidth(), (GetScreenHeight() / 8), Fade(BLACK, 0.3f), Fade(DARKBLUE, 0.005f));

	Vector2 mousePos = GetMousePosition(); //Get the mouse coordinates

<<<<<<< HEAD
   /// Entity Manager
  /* Update and draw all entities */
	for (auto entity : entities) {
		entity->Update();
		entity->Draw();
	}

	Vector2 mousePos = GetMousePosition(); //Get the mouse coordinates
	DrawRectangleGradientV(0, 0, GetScreenWidth(), (GetScreenHeight() / 8), Fade(BLACK, 0.3f), Fade(DARKBLUE, 0.005f));
	DrawText(TextFormat("X, Y: [ %i, %i ]", (int)mousePos.x, (int)mousePos.y), 10, 28, 12, RAYWHITE); //Draws the mouse coords in the top left corner
	DrawText(TextFormat("FPS: [ %i ]", (int)GetFPS()), 10, 10, 18, RAYWHITE);						 //Draws the FPS in the top left corner

	  /// DRAW SPAWN ITEMS
#pragma region [ Draw Spawn Items ]
	/* Draw the Spawn Items */
	DrawPoly({ 150, 30 }, 5, 25, 0, Color{ 10, 10, 10, 100 });
	DrawPoly({ 200, 30 }, 5, 25, 0, Color{ 10, 10, 10, 100 });
	DrawPoly({ 250, 30 }, 5, 25, 0, Color{ 10, 10, 10, 100 });

	DrawText("F", 145, 22, 20, GRAY);
	DrawText("S", 195, 22, 20, GRAY);
	DrawText("W", 245, 22, 20, GRAY);

	switch (spawnIndex) {
	case SpawnFish:
		DrawPolyLines({ 150, 30 }, 5, 26, 10, BLACK);
		DrawPolyLines({ 150, 30 }, 5, 25, 10, BLACK);
		DrawPolyLines({ 150, 30 }, 5, 24, 10, BLACK);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			entities.push_back(new Fish({ mousePos.x, mousePos.y }));
		}
		break;
	case SpawnShark:
		DrawPolyLines({ 200, 30 }, 5, 26, 10, BLACK);
		DrawPolyLines({ 200, 30 }, 5, 25, 10, BLACK);
		DrawPolyLines({ 200, 30 }, 5, 24, 10, BLACK);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			entities.push_back(new Shark({ mousePos.x, mousePos.y }));
		}
		break;
	case SpawnWhale:
		DrawPolyLines({ 250, 30 }, 5, 26, 10, BLACK);
		DrawPolyLines({ 250, 30 }, 5, 25, 10, BLACK);
		DrawPolyLines({ 250, 30 }, 5, 24, 10, BLACK);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			entities.push_back(new Whale({ mousePos.x, mousePos.y }));
		}
		break;
	default:
		break;
	}
#pragma endregion

=======
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		DrawCircle(GetMouseX(), GetMouseY(), 15, Fade(RAYWHITE, 0.1f));
		mEntity.push_back(new Fish({ mousePos.x, mousePos.y }));
	}

	for (auto fish : mEntity) {
		fish->Update();
		fish->Draw();
	}

	DrawText(TextFormat("X, Y: [ %i, %i ]", (int)mousePos.x, (int)mousePos.y), 10, 28, 12, RAYWHITE); //Draws the mouse coords in the top left corner
	DrawText(TextFormat("FPS: [ %i ]", (int)GetFPS()), 10, 10, 18, RAYWHITE);						 //Draws the FPS in the top left corner

>>>>>>> parent of ebb9e7f (fixed~)
	EndDrawing();
}

/// DEREFERENCING
/* Deference objects before exit */
void Dereference() {
	for (unsigned int i = 0; i < entities.size(); i++) { //For every entitiy
		delete entities[i];								//Delete entity
	}
	entities.clear();
}

/// Main
int main() {
	Init(); //Initialisation
<<<<<<< HEAD
	Start();
=======

	for (int i = 0; i < 1; i++) {
		mEntity.push_back(new Fish({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) }));
	}
>>>>>>> parent of ebb9e7f (fixed~)

	bool exitWindow = false;
	while (!exitWindow) {
		exitWindow = WindowShouldClose();

		Update();
		Draw();
	}

	Dereference();
	CloseWindow();
}