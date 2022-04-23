#include "Classes.h"

Sheep::Sheep(Coordinates coordinates, World& world)
	: Animal(coordinates,world) {
	this->initiative = 4;
	this->strength = 4;
}

string Sheep::draw() {
	return "@";
}

Organism* Sheep::breedCopy(Coordinates coordinates) {
	return new Sheep(coordinates, this->world);
}
