#include "GridMap.h"


 /// DRAW: Grid
/* Draws out the lines for the pathfinding grid */
void GridMap::DrawGrid(Color COLOR) {
	Vector2 linePos = { 0, 0 };

	/* Draws the map lines */
	for (int w = 0; w < (mapWidth); w++) {
		DrawLine((linePos.x), (0), (linePos.x), GetScreenHeight(), COLOR);
		linePos.x += spacing;
	}
	for (int h = 0; h < (mapHeight); h++) {
		DrawLine(0, linePos.y, GetScreenWidth(), (linePos.y), COLOR);
		linePos.y += spacing;
	}
}

void GridMap::DrawNodes(Color COLOR) {
	Vector2 nodePos = { 0, 0 };

	/* Draws the map nodes */
	for (int h = -1; h < (mapHeight); h++) {
		for (int w = -1; w < (mapWidth); w++) {
			DrawCircle(nodePos.x, nodePos.y, 2, COLOR);
			nodePos.x += spacing;
		}
		nodePos.x = 0;
		nodePos.y += spacing;
	}
}

void GridMap::DrawNodes(vector<Node*> nodes) {
	for (auto node : nodes) {
		DrawCircle(node->position.x, node->position.y, 2, ORANGE);
	}
}