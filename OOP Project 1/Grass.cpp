#include "Classes.h"

Grass::Grass(Coordinates coordinates, World& world) : Plant(coordinates, world) {
	this->strength = 0;
};

string Grass :: draw() {
	return "G";
}

Organism* Grass::sowCopy(Coordinates coordinates) {
	return new Grass(coordinates, this->world);
}