#include <ctime>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#define RAYGUI_STATIC

#include "EntityObject.h"
#include "Agent.h"
#include "AgentFish.h"
#include "AgentShark.h"
#include "AgentWhale.h"
#include "raygui.h"

#undef RAYGUI_IMPLEMENTATION

/// Variables
const int screenWidth = 1280;  //Set screen width
const int screenHeight = 720; //Set screen height

vector<EntityObject*> mEntity = {};

/// Variables: Item Select
int spawnIndex = 0;
enum SpawnArray { Empty = 0, SpawnFish, SpawnShark, SpawnWhale };


 /// INITIALISATION
/* Program initialisation */
void Init() {
	InitWindow(screenWidth, screenHeight, "Sofishticated Sea++ Program"); //Initialise raylib window dimensions and change title
	SetTargetFPS(60); //Set the target FPS

	SetExitKey(0);
}

 /// UPDATING
/* Program updates */
void Update() {
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
			spawnIndex = sizeof(SpawnArray); // Clamp
		}
	}

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		DrawCircle(GetMouseX(), GetMouseY(), 15, Fade(RAYWHITE, 0.1f));
	}
}

 /// DRAWING
/* Program drawing */
void Draw() {
	BeginDrawing();
	ClearBackground({ 23, 23, 23 });
	DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(DARKBLUE, 0.3f), Fade(BLUE, 0.005f));

	  /// Entity Manager
#pragma region [ Entity Manager ]
	/* Update and draw fish entity */
	for (auto enitity : mEntity) {
		enitity->Update();
		enitity->Draw();
	}

	for (int i = 0; i < sizeof(mEntity); i++) {
	}
#pragma endregion

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
			mEntity.push_back(new Fish({ mousePos.x, mousePos.y }));
		}
		break;
	case SpawnShark:
		DrawPolyLines({ 200, 30 }, 5, 26, 10, BLACK);
		DrawPolyLines({ 200, 30 }, 5, 25, 10, BLACK);
		DrawPolyLines({ 200, 30 }, 5, 24, 10, BLACK);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			mEntity.push_back(new Shark({ mousePos.x, mousePos.y }));
		}
		break;
	case SpawnWhale:
		DrawPolyLines({ 250, 30 }, 5, 26, 10, BLACK);
		DrawPolyLines({ 250, 30 }, 5, 25, 10, BLACK);
		DrawPolyLines({ 250, 30 }, 5, 24, 10, BLACK);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			mEntity.push_back(new Whale({ mousePos.x, mousePos.y }));
		}
		break;
	default:
		break;
	}
#pragma endregion

	EndDrawing();
}

 /// Main
int main() {
	Init(); //Initialisation

	  /// DEBUG MODE
//#ifndef NDEBUG
	/* if(BUILD IS DEBUG MODE) */
	for (int i = 0; i < 150; i++) { mEntity.push_back(new Fish({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) })); }
	//for (int i = 0; i < 5; i++) { mEntity.push_back(new Shark({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) })); }
	//for (int i = 0; i < 2; i++) { mEntity.push_back(new Whale({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) })); }
//#endif

	bool exitWindow = false;
	while (!exitWindow) {
		exitWindow = WindowShouldClose();

		Update();
		Draw();
	}

	CloseWindow();
}