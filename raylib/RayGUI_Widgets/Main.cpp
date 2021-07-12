#include "main.h"

 /// INITIALISATION
/* Program initialisation */
void Init() {
	const int screenWidth = 1280;  //Set screen width
	const int screenHeight = 720; //Set screen height

	InitWindow(screenWidth, screenHeight, "Sofishticated Sea++ Program"); //Initialise raylib window dimensions and change title
	SetTargetFPS(60); //Set the target FPS

	SetExitKey(0);
}

 /// DRAWING
/* Program drawing */
void Draw() {
	BeginDrawing();
	ClearBackground(DARKBLUE);

	DrawFPS(10, 10);

	Vector2 mousePos = GetMousePosition();
	DrawText(TextFormat("X, Y: [ %i, %i ]", (int)mousePos.x, (int)mousePos.y), 10, 50, 18, RAYWHITE);

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