#include "Everything.h"

Organism::Organism(): world() {}

Organism::Organism(int givenX, int givenY, World* givenWorld) {
	this->coordinates.x = givenX;
	this->coordinates.y = givenY;
	this->world = givenWorld;
}

int Organism::getX()
{
	return this->coordinates.x;
}

int Organism::getY()
{
	return this->coordinates.y;
}

Organism::~Organism(){};