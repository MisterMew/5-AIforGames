#include <ctime>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#define RAYGUI_STATIC

#include "EntityObject.h"
#include "Fish.h"
#include "raygui.h"

#undef RAYGUI_IMPLEMENTATION

/// Variables
const int screenWidth = 1280;  //Set screen width
const int screenHeight = 720; //Set screen height

vector<EntityObject*> mEntity = {};


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
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		DrawCircle(GetMouseX(), GetMouseY(), 15, Fade(RAYWHITE, 0.1f));
		mEntity.push_back(new Fish(GetMouseX(), GetMouseY()));
	}
}

 /// DRAWING
/* Program drawing */
void Draw() {
	BeginDrawing();
	ClearBackground({ 23, 23, 23 });
	DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(DARKBLUE, 0.3f), Fade(BLUE, 0.005f));
	DrawRectangleGradientV(0, 0, GetScreenWidth(), (GetScreenHeight() / 8), Fade(BLACK, 0.3f), Fade(DARKBLUE, 0.005f));

	Vector2 mousePos = GetMousePosition(); //Get the mouse coordinates
	DrawText(TextFormat("X, Y: [ %i, %i ]", (int)mousePos.x, (int)mousePos.y), 10, 28, 12, RAYWHITE); //Draws the mouse coords in the top left corner
	DrawText(TextFormat("FPS: [ %i ]", (int)GetFPS()), 10, 10, 18, RAYWHITE);						 //Draws the FPS in the top left corner

	for (auto fish : mEntity) {
		fish->Update();
		fish->Draw();
	}
	
	EndDrawing();
}

 /// Main
int main() {
	Init(); //Initialisation

	for (int i = 0; i < 200; i++) {
		mEntity.push_back(new Fish(screenWidth / 2, screenHeight / 2));
	}
	for (int i = 0; i < 200; i++) {
		mEntity[i]->Start();
	}

	bool exitWindow = false;
	while (!exitWindow) {
		exitWindow = WindowShouldClose();

		Update();
		Draw();
	}

	CloseWindow();
}