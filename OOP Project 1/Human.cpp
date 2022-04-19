#include "Everything.h"
#include <conio.h>
#include <string>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define X_SIGN 120
#define Q_SIGN 113

Human::Human(Coordinates coordinates, World& world) 
	: Animal(coordinates, world) {
	this->strength = 5;
	this->initiative = 4;
}
string Human::draw() {
	return "?";
}

void Human::action() {
	cout << "Human Action" << endl;
	cout << "Arrows to move, q to activate special ability, x to finish Human Action" << endl;

	int input = 0;
	int direction = -1;

	while (true)
	{
		int toBreak = 0;
		switch ((input = _getch())) {
		case X_SIGN:
			toBreak = 1;
			break;
		case KEY_UP:
			direction = UP;
			cout << "UP" << endl;
			break;
		case KEY_RIGHT:
			direction = RIGHT;
			cout << "RIGHT" << endl;
			break;
		case KEY_DOWN:
			direction = DOWN;
			cout << "DOWN" << endl;
			break;
		case KEY_LEFT:
			direction = LEFT;
			cout << "LEFT" << endl;
			break;
		case Q_SIGN:
			this->special_ability = true;
			cout << "Special ability activated" << endl;
		}
		if (checkCoordinates(direction) == false)
		{
			cout << "Choose proper direction or do not choose any direction" << endl;
			toBreak = 0;
		}
		if (toBreak == 1)
			break;
	}

	if(direction != -1)
		changeHumanPosition();

	if (special_ability)
		purification();
}

bool Human::checkCoordinates(int direction) {
	int newX = this->coordinates.x;
	int newY = this->coordinates.y;

	if (direction == UP)
		newX--;
	else if (direction == RIGHT)
		newY++;
	else if (direction == DOWN)
		newX++;
	else if (direction == LEFT)
		newY--;

	if (newX >= this->world.getWidth() || newX < 0 || newY >= this->world.getHeight() || newY < 0)
	{
		cout << "You tried to go out of this world" << endl;
		return false;
	}
	else
	{
		this->newCoordinates = { newX,newY };
		return true;
	}	
}

void Human::changeHumanPosition() {

		world.board[coordinates.x][coordinates.y] = NULL;
		this->coordinates.y = newCoordinates.y;
		this->coordinates.x = newCoordinates.x;
		world.board[coordinates.x][coordinates.y] = this;
}

void Human::purification() {
	for (int i = 0; i < arrComb.size(); i++)
	{
		int newX = this->coordinates.x + arrComb[i].x;
		int newY = this->coordinates.y + arrComb[i].y;

		if (newX >= this->world.getWidth() || newX < 0 || newY >= this->world.getHeight() || newY < 0)
			continue;

		Organism* orgToKill = world.board[newX][newY];

		if (orgToKill != NULL)
		{
			world.board[orgToKill->getX()][orgToKill->getY()] = NULL;

			for (int i = 0; i < world.organisms.size(); i++)
			{
				if (world.organisms[i] == orgToKill)
				{
					world.organisms.erase(world.organisms.begin() + i);
				}
			}
			world.comments.push_back("Organism " + orgToKill->draw() + " has been killed by Organism " + this->draw() + " at position x:" + to_string(orgToKill->getX()) + " y: " + to_string(orgToKill->getY()));
		}
		
		
	}
}