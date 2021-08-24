#include "GridMap.h"

Node* GridMap::map[mapHeight][mapWidth]; //Defines 'map' so it can be initialised

#pragma region [ Graph Functions ]

void GridMap::CreateGridNetwork() {
	Vector2 pos = { 0, 0 };
	for (int h = 0; h < (mapHeight); h++) {
		for (int w = 0; w < (mapWidth); w++) {
			Node* newNode = new Node(pos, {(float)h, (float)w});		 //Create a new Node
			newNode->SetPos( Vector2{ pos.x, pos.y } ); //Set its position on the screen
			map[h][w] = newNode;					   //Set the map element to the node

			tempList.push_back(map[h][w]); /// map is an array of nodes, here trying to push each node into a list... ///

			pos.x += 20;
		}
		pos.x = 0;
		pos.y += 20;
	}
}

void GridMap::CreateConnections() { //node is the Node we want to create connections from.
	for (int h = 0; h <= mapHeight; h++) {
		for (int w = 0; w <=  mapWidth; w++) {

			Node* newNode = new Node();
			Vector2 nodeGridPos = newNode->GetGridPos(); //Get nodeA's position in the grid

			if (nodeGridPos.x >= 0 && nodeGridPos.x < mapWidth && nodeGridPos.y >= 0 && nodeGridPos.y < mapHeight ) { //Do a safety check
				if (h < mapHeight - 1) { newNode->connections.push_back(Edge{ map[h + 1][w], axialDist }); }
				if (w < mapWidth - 1)  { newNode->connections.push_back(Edge{ map[h][w + 1], axialDist }); }
				if (h > 0) { newNode->connections.push_back(Edge{ map[h - 1][w], axialDist }); }
				if (w > 0) { newNode->connections.push_back(Edge{ map[h][w - 1], axialDist }); }
			}
		}
	}
}

#pragma endregion
#pragma region [ Draw Functions ]

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

 /// DRAW: Nodes
/* Draw a circle for every node in the map */
void GridMap::DrawNodes(Color COLOR) {
	if (map == NULL) { return; }
	for (int h = 0; h < (mapHeight); h++) {
		for (int w = 0; w < (mapWidth); w++) {
			DrawCircle(map[h][w]->GetPos().x, map[h][w]->GetPos().y, 2, COLOR);
		}
	}
}

 /// DRAW: Path
/* Draw the AI path */
void GridMap::DrawPath(Node* startNode, Node* endNode) {
	for (Edge edge : startNode->connections) {
		DrawLine(startNode->GetGridPos().x, startNode->GetGridPos().y, edge.GetNeighbour()->GetGridPos().x, edge.GetNeighbour()->GetGridPos().y, ORANGE);
	}

	DrawCircle(startNode->GetGridPos().x, startNode->GetGridPos().y, 3, PALEGREEN); //Draw the start node
	DrawCircle(endNode->GetGridPos().x, endNode->GetGridPos().y, 3, PALERED); //Draw the end/target node
}

#pragma endregion