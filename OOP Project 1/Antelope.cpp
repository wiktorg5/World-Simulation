#include "Everything.h"

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
		newCoordinates = makeNewXYAfterFight(this->newCoordinates);

		
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

Coordinates Antelope::makeNewXYAfterFight(Coordinates coordinates) {

	srand(time(0));
	vector<Coordinates> arrXY = arrComb;

	int randCombination = rand() % arrXY.size();
	Coordinates randomXY = arrXY[randCombination];

	int newX = randomXY.x + coordinates.x;
	int newY = randomXY.y + coordinates.y;

	while (true)
	{
		if (newX >= this->world.getWidth() || newX < 0 || newY >= this->world.getHeight() || newY < 0 || world.board[newX][newY] != NULL)
		{
			arrXY.erase(arrXY.begin() + randCombination);
			if (arrXY.size() == 0)
			{
				return coordinates;
			}
			else
			{
				randCombination = rand() % arrXY.size();
				randomXY = arrXY[randCombination];
				newX = randomXY.x + coordinates.x;
				newY = randomXY.y + coordinates.y;
			}
		}
		else
		{
			randomXY.x = newX;
			randomXY.y = newY;
			return randomXY;
		}
	}
}

Organism* Antelope::breedCopy(Coordinates coordinates) {
	return new Antelope(coordinates, this->world);
}