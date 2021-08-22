#include "GridMap.h"


 /// DRAW: Grid Lines
/* Draws out the lines for the grid */
void GridMap::DrawGrid(Color COLOR) {
	Vector2 linePos = { 0, 0 };

	/* Draws the map lines */
	for (int w = 0; w < (mapWidth); w++) {
		DrawLine((linePos.x), (0), (linePos.x), GetScreenHeight(), COLOR);
		linePos.x += gridSpacing;
	}
	for (int h = 0; h < (mapHeight); h++) {
		DrawLine(0, linePos.y, GetScreenWidth(), (linePos.y), COLOR);
		linePos.y += gridSpacing;
	}
}

/// DRAW: Grid Points
/* Draws out the intersectiong points for the grid */
void GridMap::DrawIntersects(Color COLOR) {
	Vector2 nodePos = { 0, 0 };

	/* Draws the map nodes */
	for (int h = 0; h < (mapHeight); h++) {
		for (int w = 0; w < (mapWidth); w++) {
			DrawCircle(nodePos.x, nodePos.y, 2, COLOR);
			nodePos.x += gridSpacing;
		}
		nodePos.x = 0;
		nodePos.y += gridSpacing;
	}
}

void GridMap::DrawNodes(Color COLOR) {
	if (map == NULL) { return; }
	for (int h = 0; h < (mapHeight); h++) {
		for (int w = 0; w < (mapWidth); w++) {
			Node* newNode = new Node();
			DrawCircle(map[h][w]->mPosition.x, map[h][w]->mPosition.y, 2, COLOR);
		}
	}
}

void GridMap::DrawNode(Node* node, bool selected) {
	//Draw the inner circle
	if (selected) { DrawCircle(node->mPosition.x, node->mPosition.y, 3, Color{ 250,3,95,255 }); }
	else { DrawCircle(node->mPosition.x, node->mPosition.y, 3, Color{ 195,250,3,255 }); }
}