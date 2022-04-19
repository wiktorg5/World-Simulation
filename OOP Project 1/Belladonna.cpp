#include "Everything.h"

Belladonna::Belladonna(Coordinates coordinates, World& world) : Plant(coordinates, world) {
	this->strength = 99;
};

string Belladonna::draw() {
	return "U";
}

Organism* Belladonna::sowCopy(Coordinates coordinates) {
	return new Belladonna(coordinates, this->world);
}