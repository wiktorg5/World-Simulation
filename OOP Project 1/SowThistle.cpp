#include "Everything.h"

SowThistle::SowThistle(Coordinates coordinates, World& world) : Plant(coordinates, world) {
	this->strength = 0;
	this->sowTries = 3;
};

string SowThistle::draw() {
	return "S";
}

Organism* SowThistle::sowCopy(Coordinates coordinates) {
	return new SowThistle(coordinates, this->world);
}