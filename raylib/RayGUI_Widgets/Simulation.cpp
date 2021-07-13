#include "simulation.h"


void Entity::SpawnEntity() {
	DrawEntity();


}

void Entity::DrawEntity() {
	DrawRectangle(GetCentre().x, GetCentre().y, 10, 10, WHITE);
}