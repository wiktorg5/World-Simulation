#include "Everything.h"
#include<string>

Organism::Organism(Coordinates coordinates,World& world) : world(world){
	this->coordinates = coordinates;
}

void Organism::setCoordinates(Coordinates newCoordinates) {
	this->coordinates = newCoordinates;
}

int Organism::getX(){
	return this->coordinates.x;
}

int Organism::getY(){
	return this->coordinates.y;
}

int Organism::getNewX() {
	return this->newCoordinates.x;
}

int Organism::getNewY() {
	return this->newCoordinates.y;
}

Coordinates Organism::getCoordinates() {
	return this->coordinates;
}

Coordinates Organism::makeNewXYToSow(Coordinates coordinates) {

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

string Organism::OrgToString() {

	string org;

	org += this->draw();
	org += " ";
	org += to_string(this->age);
	org += " ";
	org += to_string(this->getX());
	org += " ";
	org += to_string(this->getY());

	return org;
}

Organism::~Organism(){};