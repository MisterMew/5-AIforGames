#include "GridMap.h"

Node* GridMap::map[mapHeight][mapWidth]; //Defines 'map' so it can be initialised

#pragma region [ Graph Functions ]

void GridMap::CreateGridNetwork() {
	Vector2 pos = { 0, 0 };
	for (int h = 0; h < mapHeight; h++) {
		for (int w = 0; w < mapWidth; w++) {
			Node* newNode = new Node(pos, {(float)w, (float)h}); //Create a new Node (h,w swapped, constructor uses a vector2)
			newNode->SetPos( Vector2{ pos.x, pos.y } );		    //Set its position on the screen
			map[h][w] = newNode;							   //Set the map element to the node

			tempList.push_back(map[h][w]);

			pos.x += gridSpacing;
		}
		pos.x = 0;
		pos.y += gridSpacing;
	}
}

void GridMap::CreateConnections() { //node is the Node we want to create connections from.
	for (int h = 0; h < mapHeight; h++) {
		for (int w = 0; w <  mapWidth; w++) {

			Node* getNode = map[h][w];					  //Get the node at the h,w position
			Vector2 nodeGridPos = getNode->GetGridPos(); //Get nodeA's position in the grid
			if (nodeGridPos.x >= 0 && nodeGridPos.x < mapWidth && nodeGridPos.y >= 0 && nodeGridPos.y < mapHeight ) { //Do a safety check
				if (h < mapHeight - 1) { getNode->connections.push_back(Edge{ map[h + 1][w], axialDist }); }
				if (w < mapWidth - 1)  { getNode->connections.push_back(Edge{ map[h][w + 1], axialDist }); }
				if (h > 0) { getNode->connections.push_back(Edge{ map[h - 1][w], axialDist }); }
				if (w > 0) { getNode->connections.push_back(Edge{ map[h][w - 1], axialDist }); }
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
void GridMap::DrawPath(vector<Node*>& path) {
	for (unsigned int i = 0; i < path.size(); i++) {
		Vector2 pos = path[i]->GetPos();
		Color color = ORANGE;

		if (i == path.size() - 1) { color = PALEGREEN; } // Start node
		else if (i == 0) { color = PALERED; } // End node (reverse order)

		DrawCircle(pos.x, pos.y, 3, color);

		//for (Edge edge : path[i]->connections) {
		//	DrawLine(pos.x, pos.y, edge.GetNeighbour()->GetPos().x, edge.GetNeighbour()->GetPos().y, ORANGE);
		//}
	}
}

Node* GridMap::AlignVectorToGrid(Vector2 worldPos) {
	Vector2 newPosition;							   //Create a new vector
	newPosition.x = floor(worldPos.x / gridSpacing);  //Convert X to grid axis W
	newPosition.y = floor(worldPos.y / gridSpacing); //Convert Y to grid axis H

	Node* node = map[(int)newPosition.y][(int)newPosition.x]; //Set the node to the grid position
	return node;
}

Node* GridMap::AlignMouseClickToGrid(Vector2* mousePos) {
	Vector2* newPosition = mousePos;						  //Create a new vector
	newPosition->x = floor((int)mousePos->x / gridSpacing);  //Convert X to grid axis W
	newPosition->y = floor((int)mousePos->y / gridSpacing); //Convert Y to grid axis H

	Node* node = map[(int)newPosition->y][(int)newPosition->x]; //Set the node to the grid position
	return node;
}

Vector2 GridMap::AlignPositionToGrid(Vector2 worldPos) {
	Vector2 newPosition;							   //Create a new vector
	newPosition.x = floor(worldPos.x / gridSpacing);  //Convert X to grid axis W
	newPosition.y = floor(worldPos.y / gridSpacing); //Convert Y to grid axis H

	Node* node = map[(int)newPosition.y][(int)newPosition.x]; //Set the node to the grid position
	return node->GetPos();
}

#pragma endregion