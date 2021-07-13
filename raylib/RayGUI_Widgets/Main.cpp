//#include "main.h"
#include "simulation.h"
#include <iostream>
#include <string>

using namespace std;

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#define RAYGUI_STATIC

#include "raygui.h"

#undef RAYGUI_IMPLEMENTATION

/// Variables
const int screenWidth = 1280;  //Set screen width
const int screenHeight = 720; //Set screen height


 /// INITIALISATION
/* Program initialisation */
void Init() {

	InitWindow(screenWidth, screenHeight, "Sofishticated Sea++ Program"); //Initialise raylib window dimensions and change title
	SetTargetFPS(60); //Set the target FPS

	SetExitKey(0);
}

 /// DRAWING
/* Program drawing */
void Draw() {
	BeginDrawing();
	ClearBackground(Color{ 0, 105, 148 });

	//Draw: Menu bar
	DrawRectangleGradientV(0, 0, GetScreenWidth(), (GetScreenHeight() / 8), Fade(BLACK, 0.99f), Fade(DARKBLUE, 0.05f));

	//DrawText: fps
	DrawText(TextFormat("FPS: [ %i ]", (int)GetFPS()), 10, 10, 18, RAYWHITE);

	//DrawText: Mouse Pos
	Vector2 mousePos = GetMousePosition();
	DrawText(TextFormat("X, Y: [ %i, %i ]", (int)mousePos.x, (int)mousePos.y), 10, 28, 18, RAYWHITE);

	//Draw: MouseButton Splash
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		DrawCircle((int)mousePos.x, (int)mousePos.y, 15, Fade(DARKBLUE, 0.5f));
	Entity* fish = new Entity();
	fish->SpawnEntity();
	}

	
	EndDrawing();
}

 /// Main
int main() {
	Init(); //Initialisation

	bool exitWindow = false;
	while (!exitWindow) {
		exitWindow = WindowShouldClose();

		Draw();
	}

	CloseWindow();
}