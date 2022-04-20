#include "Everything.h"

Fox::Fox(Coordinates coordinates, World& world)
	: Animal(coordinates,world) {
	this->initiative = 7;
	this->strength = 3;
}

string Fox::draw() {
	return "&";
}

Coordinates Fox::makeNewXY(Coordinates coordinates) {

	srand(time(0));
	vector<Coordinates> arrXY = arrComb;

	int randCombination = rand() % arrXY.size();
	Coordinates randomXY = arrXY[randCombination];

	int newX = randomXY.x + coordinates.x;
	int newY = randomXY.y + coordinates.y;

	while (true)
	{
		if (newX >= this->world.getWidth() || newX < 0 || newY >= this->world.getHeight() || newY < 0 || world.board[randomXY.x][randomXY.y]->getStrength() > this->getStrength())
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
			break;
		}
	}
	return randomXY;
}

Organism* Fox::breedCopy(Coordinates coordinates) {
	return new Fox(coordinates, this->world);
}
