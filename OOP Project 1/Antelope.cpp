#include "Classes.h"

Antelope::Antelope(Coordinates coordinates, World& world)
	: Animal(coordinates,world) {
	this->initiative = 4;
	this->strength = 4;
}

string Antelope::draw() {
	return "$";
}

void Antelope::backFromFight(Antelope* org) {
	Coordinates newCoordinates;
		newCoordinates = makeNewXYNULL(this->newCoordinates);

		
		if (world.board[newCoordinates.x][newCoordinates.y] == NULL)
		{
			if (org == this)
			{
				world.board[newCoordinates.x][newCoordinates.y] = this;
				world.board[coordinates.x][coordinates.y] = NULL;
				this->coordinates = newCoordinates;
				return;
			}
			else
			{
				world.board[newCoordinates.x][newCoordinates.y] = org;
				world.board[org->coordinates.x][org->coordinates.y] = NULL;
				org->coordinates = newCoordinates;
				world.board[this->newCoordinates.x][this->newCoordinates.y] = this;
				world.board[coordinates.x][coordinates.y] = NULL;
				this->coordinates = this->newCoordinates;
				return;
			}
		}
		else
			this->basicCollision();
}

Organism* Antelope::breedCopy(Coordinates coordinates) {
	return new Antelope(coordinates, this->world);
}