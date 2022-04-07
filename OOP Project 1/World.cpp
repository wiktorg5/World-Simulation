#include "Everything.h"

World::World(int widthGiven, int heightGiven)
{
	this->height = heightGiven;
	this->width = widthGiven;

	for (int i = 0; i < height; i++)
	{
		board.push_back(vector<Organism*>());

		for (int k = 0; k < width; k++)
			this->board[i].push_back(NULL);
	}
}

int World::getWidth() {
	return width;
}
int World::getHeight() {
	return height;
}

void World::firstOrganisms() {
	int numberOfOrganisms = (height * width) / 15;
	if (numberOfOrganisms == 0)
		numberOfOrganisms = 1;

	srand(time(0));
	int x, y;
	for (int k = 0; k < numberOfOrganisms; k++)
	{
		do {
			x = rand() % width;
			y = rand() % height;
			if (board[x][y] == NULL)
			{
				board[x][y] = new Wolf(x, y, this);
				break;
			}
		} while (board[x][y] == NULL);

		organisms.push_back(board[x][y]);
	}
}

void World::printBoard() {
	for (int i = 0; i < board.size(); i++)
	{
		for (int k = 0; k < board[i].size(); k++)
		{
			if (board[i][k] == NULL)
				cout << " ";
			else
				cout << board[i][k]->draw();
		}
		cout << endl;
	}
	cout << "---------------------------" << endl;
}

void World::newTurn() {
	if (this->turnNumber == 0)
		firstOrganisms();
	else
	{
		for (int i = 0; i < organisms.size(); i++)
		{
			organisms[i]->action();
		}
	}
	turnNumber++;
}

void World::moveAfterKill(Organism* killedOrganism, Organism* winOrganism){
	board[killedOrganism->getX()][killedOrganism->getY()] = winOrganism; 
	board[winOrganism->getX()][winOrganism->getY()] = NULL;
	
}
void World::kill(Organism* killedOrganism, Organism* winOrganism) {
	for (int i = 0; i < organisms.size(); i++)
	{
		if (organisms[i] == killedOrganism)
		{
			moveAfterKill(killedOrganism, winOrganism);
			organisms.erase(organisms.begin() + i);
		}
	}

}