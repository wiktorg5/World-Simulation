#include "Everything.h"
#include <conio.h>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define X_SIGN 120

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
			toBreak=1;
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
		}
		if (toBreak == 1)
			break;
	}
	cout << direction << endl;
	if(direction != -1)
		changeHumanPosition(direction);
	
}

void Human::changeHumanPosition(int direction) {

	int newX = this->coordinates.x;
	int newY = this->coordinates.y;

	if (direction == UP)
	{
		newX--;
	}
	else if (direction == RIGHT)
	{
		newY++;
	}
	else if (direction == DOWN)
	{
		newX++;
	}
	else if (direction == LEFT)
	{
		newY--;
	}
	if (newX >= this->world.getWidth() || newX < 0 || newY >= this->world.getHeight() || newY < 0)
	{
		cout << "You tried to go out of this world" << endl;
	}
	else
	{
		world.board[coordinates.x][coordinates.y] = NULL;
		this->coordinates.y = newY;
		this->coordinates.x = newX;
		world.board[coordinates.x][coordinates.y] = this;
	}	
}