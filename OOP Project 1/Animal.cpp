#include "Classes.h"

Animal::Animal(Coordinates coordinates,World& world)
	: Organism(coordinates,world) {}

//choosing new coordinates to move 
Coordinates Animal::makeNewXY(Coordinates coordinates) {

	vector<Coordinates> arrXY = arrComb;

	//if it's Turtle there will be 75% of {0,0} points to choose from
	if (Turtle* v = dynamic_cast<Turtle*>(this))
	{
		for (int i = 0; i < 20; i++) {
			arrXY.push_back({ 0,0 });
		}
	}
	
	int randCombination = rand() % arrXY.size();
	Coordinates randomXY = arrXY[randCombination];

	int newX = randomXY.x + coordinates.x;
	int newY = randomXY.y + coordinates.y;
	
	while (true)
	{
		if (newX >= this->world.getWidth() || newX < 0 || newY >= this->world.getHeight() || newY < 0)
		{
			// if there is no possible move we do not move
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
void Animal::action() {
	Coordinates newCoordinates = this->makeNewXY(this->coordinates);
	
	this->newCoordinates = newCoordinates;

	// if cell is empty we move there, else we collide with another object
	if (world.board[newCoordinates.x][newCoordinates.y] == NULL)
	{
		world.board[newCoordinates.x][newCoordinates.y] = this;
		world.board[coordinates.x][coordinates.y] = NULL;
		this->coordinates = this->newCoordinates;
	}
	else if(this->newCoordinates.x == this->coordinates.x && this->newCoordinates.y == this->coordinates.y)
	{
		return;
	}
	else 
	{
		collision();
	}	
}

void Animal::basicCollision() {
	
	if (world.board[this->newCoordinates.x][this->newCoordinates.y]->getStrength() < this->strength)
		world.kill(*world.board[this->newCoordinates.x][this->newCoordinates.y], *this, *this);

	else if (world.board[this->newCoordinates.x][this->newCoordinates.y]->getStrength() > this->strength)
		world.kill(*this, *world.board[this->newCoordinates.x][this->newCoordinates.y],*this);

	else if (typeid(*this->world.board[newCoordinates.x][newCoordinates.y]) == typeid(*this))
		this->breeding(world.board[newCoordinates.x][newCoordinates.y]);
	else
		world.kill(*world.board[this->newCoordinates.x][this->newCoordinates.y], *this,*this);
}
void Animal::collision() {

	int chanceToBackFight = rand() % 100;

	// we choose collision mode basing on object colliding
	if (Turtle* v = dynamic_cast<Turtle*>(world.board[this->newCoordinates.x][this->newCoordinates.y]))
	{
		if (this->strength > 5)
		{
			this->basicCollision();
		}
	}
	else if (Antelope* v = dynamic_cast<Antelope*>(world.board[this->newCoordinates.x][this->newCoordinates.y]))
	{
		if (chanceToBackFight >= 50)
			dynamic_cast<Antelope*>(world.board[this->newCoordinates.x][this->newCoordinates.y])->backFromFight(dynamic_cast<Antelope*>(world.board[this->newCoordinates.x][this->newCoordinates.y]));
		else
			this->basicCollision();
	}
	else if (Antelope* v = dynamic_cast<Antelope*>(this))
	{
		if (chanceToBackFight >= 50)
			dynamic_cast<Antelope*>(this)->backFromFight(dynamic_cast<Antelope*>((this)));
		else
			this->basicCollision();
	}
	else if (Guarana* v = dynamic_cast<Guarana*>(world.board[this->newCoordinates.x][this->newCoordinates.y]))
	{
		this->strength += 3;
	}
	else
		this->basicCollision();
}

void Animal::breeding(Organism* secondAnimal) {

	Coordinates newOrganismCoordinates;

	//choosing by which parent new animal will spawn
	int byWhichSpawn = rand() % 100;
	if (byWhichSpawn < 50)
	{
		newOrganismCoordinates = makeNewXYNULL(this->coordinates);
	}
	else
	{
		newOrganismCoordinates = makeNewXYNULL(secondAnimal->getCoordinates());
	}
	this->breedBasic(newOrganismCoordinates);
	cout << "Breeding" << endl;
}

void Animal::breedBasic(Coordinates newOrganismCoordinates) {
	if (newOrganismCoordinates.x == this->coordinates.x && newOrganismCoordinates.y == this->coordinates.y)
		return;
	else
	{
		Organism* newOrg = this->breedCopy(newOrganismCoordinates);
		cout << newOrg->draw() << endl;
		this->world.AnimalsToAdd.push_back(newOrg);
	}
}