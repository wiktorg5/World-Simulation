#include "Everything.h"

Wolf::Wolf() {};

Wolf::Wolf(int givenX, int givenY, World* givenWorld) {
	this->initiative = 4;
	this->strength = 9;
}

char Wolf::draw() {
	return '!';
}