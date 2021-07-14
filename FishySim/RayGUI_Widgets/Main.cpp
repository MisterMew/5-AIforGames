#include <vector>
#include <ctime>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#define RAYGUI_STATIC

#include "simulation.h"
#include "raygui.h"

#undef RAYGUI_IMPLEMENTATION

/// Variables
const int screenWidth = 1280;  //Set screen width
const int screenHeight = 720; //Set screen height

vector<Entity> entities;


 /// INITIALISATION
/* Program initialisation */
void Init() {

	InitWindow(screenWidth, screenHeight, "Sofishticated Sea++ Program"); //Initialise raylib window dimensions and change title
	SetTargetFPS(60); //Set the target FPS

	SetExitKey(0);
}

void Update() {
	for (Entity& fish : entities) {
		fish.UpdateEntity();
		fish.RenderFish();
	}
}

 /// DRAWING
/* Program drawing */
void Draw() {
	BeginDrawing();
	ClearBackground({ 23, 23, 23 });
	DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(DARKBLUE, 0.3f), Fade(BLUE, 0.005f));


	//Draw: Menu bar
	DrawRectangleGradientV(0, 0, GetScreenWidth(), (GetScreenHeight() / 8), Fade(BLACK, 0.3f), Fade(DARKBLUE, 0.005f));

	//DrawText: fps
	DrawText(TextFormat("FPS: [ %i ]", (int)GetFPS()), 10, 10, 18, RAYWHITE);

	//DrawText: Mouse Pos
	Vector2 mousePos = GetMousePosition();
	DrawText(TextFormat("X, Y: [ %i, %i ]", (int)mousePos.x, (int)mousePos.y), 10, 28, 18, RAYWHITE);

	//Draw: MouseButton Splash
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		DrawCircle((int)mousePos.x, (int)mousePos.y, 15, Fade(BLUE, 0.4f));

		entities.push_back(Entity({ mousePos.x, mousePos.y }, {1, 3}, GetRandomValue(20, 100) / 50.0 ));
	}
	
	EndDrawing();
}

 /// Main
int main() {
	Init(); //Initialisation

	for (int i = 0; i < 20; ++i) {
		entities.push_back(Entity({
			(float)GetRandomValue(0, screenWidth),
			(float)GetRandomValue(0, screenHeight), 
		}, {
			(float)GetRandomValue(-5, 5),
			(float)GetRandomValue(-5, 5),
		},
		GetRandomValue(40, 80) / 50.0
		));
	}

	bool exitWindow = false;
	while (!exitWindow) {
		exitWindow = WindowShouldClose();

		Update();
		Draw();
	}

	CloseWindow();
}