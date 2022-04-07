#include "Everything.h"

Animal::Animal() {};

Animal::Animal(int givenX, int givenY, World* givenWorld) {
	this->coordinates.x = givenX;
	this->coordinates.y = givenY;
}
void Animal::action() {
	srand(time(0));
	int randArr[] = {-1, 0, 1};
	int x, y;
	x = getX() + randArr[ rand() % 3];
	y = getY() + randArr[rand() % 3];

	while (true)
	{
		if (x > world->getWidth() || x<0 || y>world->getHeight() || y < 0)
		{
			x = getX() + randArr[rand() % 3];
			y = getY() + randArr[rand() % 3];
		}
		else
			break;
	}
	
	this->newX = x;
	this->newY = y;

	if (world->board[x][y] != NULL)
	{
		world->board[coordinates.x][coordinates.y] = NULL;
		world->board[newX][newY] = this;
		coordinates.x = newX;
		coordinates.y = newY;
	}
	else
		collision();
}

void Animal::collision() {
	if (world->board[newX][newY]->getStrength() < this->strength)
		world->kill(world->board[newX][newY],this);
	else
		world->kill(this, world->board[newX][newY]);
}