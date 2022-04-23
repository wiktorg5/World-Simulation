#include "Classes.h"

Wolf::Wolf(Coordinates coordinates, World& world)
	:Animal(coordinates,world) {
	this->initiative = 5;
	this->strength = 9;
}

string Wolf::draw() {
	return "!";
}

Organism* Wolf::breedCopy(Coordinates coordinates) {
	return new Wolf(coordinates, this->world);
}
