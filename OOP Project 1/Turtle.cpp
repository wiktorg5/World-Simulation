#include "Everything.h"

Turtle::Turtle(Coordinates coordinates, World& world)
	: Animal(coordinates,world) {
	this->initiative = 1;
	this->strength = 2;
}

string Turtle::draw() {
	return "#";
}

Organism* Turtle::breedCopy(Coordinates coordinates) {
	return new Turtle(coordinates, this->world);
}

