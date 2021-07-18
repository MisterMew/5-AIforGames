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

EntityObject* entity = new EntityObject();
vector<EntityObject> fish;
vector<EntityObject> shark;


 /// INITIALISATION
/* Program initialisation */
void Init() {
	InitWindow(screenWidth, screenHeight, "Sofishticated Sea++ Program"); //Initialise raylib window dimensions and change title
	SetTargetFPS(60); //Set the target FPS

	SetExitKey(0);
}

void Update() {
	for (EntityObject& fish : fish) {
		fish.RenderFish();
		fish.UpdateEntity();
	}

	for (EntityObject& shark : shark) {
		shark.RenderShark();
		shark.UpdateEntity();
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
	DrawText(TextFormat("X, Y: [ %i, %i ]", (int)mousePos.x, (int)mousePos.y), 10, 28, 18, RAYWHITE); //Draws the mouse coords in the top left corner
	DrawText(TextFormat("FPS: [ %i ]", (int)GetFPS()), 10, 10, 18, RAYWHITE); //Draws the FPS in the top left corner

	//Draw: MouseButton Splash
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		DrawCircle((int)mousePos.x, (int)mousePos.y, 15, Fade(BLUE, 0.4f));

		shark.push_back(EntityObject ({ mousePos.x, mousePos.y }, { (float)GetRandomValue(-5, 5), (float)GetRandomValue(-5, 5) }, true));
	}
	
	EndDrawing();
}

 /// Main
int main() {
	Init(); //Initialisation

	for (int i = 0; i < 200; ++i) {
		fish.push_back(EntityObject({
			(float)GetRandomValue(0, screenWidth),
			(float)GetRandomValue(0, screenHeight), 
		}, {
			(float)GetRandomValue(-5, 5),
			(float)GetRandomValue(-5, 5),
		}, 2.0f ));
	}

	bool exitWindow = false;
	while (!exitWindow) {
		exitWindow = WindowShouldClose();

		Draw();
		Update();
	}

	CloseWindow();
}