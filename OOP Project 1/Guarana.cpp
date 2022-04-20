#include "Everything.h"

Guarana::Guarana(Coordinates coordinates, World& world) : Plant(coordinates, world) {
	this->strength = 0;
};

string Guarana::draw() {
	return "g";
}

Organism* Guarana::sowCopy(Coordinates coordinates) {
	return new Guarana(coordinates, this->world);
}