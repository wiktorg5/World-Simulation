#include "World.h"
#include<string>
#include<algorithm>
#include<fstream>

//constructing world with board of NULLs
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

//sorting of alive organisms vector
void World::sortOrganisms() {
	sort(organisms.begin(), organisms.end(), compareOrganisms);
}
bool World::compareOrganisms(Organism* org1, Organism* org2) {
	if(org1->initiative > org2->initiative) return true;
	if (org1->initiative < org2->initiative) return false;

	if (org1->age > org2->age) return true;
	if (org1->age < org2->age) return false;

	return false;
}

int World::getWidth() {
	return this->width;
}
int World::getHeight() {
	return this->height;
}

Organism* World::getRandomOrganism(int x,int y) {

	int randomNum = rand() % 100;
	Organism* org = NULL;

	if (randomNum >= 0 && randomNum <= 10)
		org = new Wolf({ x, y }, *this);
	else if (randomNum > 10 && randomNum <= 20)
		org = new Sheep({ x, y }, *this);
	else if (randomNum > 20 && randomNum <= 30)
		org = new Turtle({ x, y }, *this);
	else if (randomNum > 30 && randomNum <= 40)
		org = new Fox({ x, y }, *this);
	else if (randomNum > 40 && randomNum <= 50)
		org = new Antelope({ x, y }, *this);
	else if (randomNum > 50 && randomNum <= 60)
		org = new Grass({ x, y }, *this);
	else if (randomNum > 60 && randomNum <= 70)
		org = new SowThistle({ x, y }, *this);
	else if (randomNum > 70 && randomNum <= 80)
		org = new Belladonna({ x, y }, *this);
	else if (randomNum > 80 && randomNum <= 90)
		org = new Guarana({ x, y }, *this);
	else
		org = new Hogweed({ x, y }, *this);

	return org;
}

//populating board with random organisms at start
void World::firstOrganisms() {
	int numberOfOrganisms = (height * width) / 20;
	if (numberOfOrganisms == 0)
		numberOfOrganisms = 1;

	int x, y;
	for (int k = 0; k < numberOfOrganisms; k++)
	{
		x = rand() % width;
		y = rand() % height;

		Organism* org = NULL;

		while (true)
		{
			if (this->board[x][y] == NULL)
			{
				if (k == 0)
					org = new Human({ x,y }, *this);
				else
					org = getRandomOrganism(x,y);
			}
			else
			{
				x = rand() % width;
				y = rand() % height;
			}
			if(org!=NULL)
				break;
		}

		this->board[x][y] = org;
		organisms.push_back(org);		
	}
}

void World::printBoard() {

	system("CLS");

	cout << "World Simulation by Wiktor Wysocki 188628" << endl;

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
	cout << "Turn " + to_string(turnNumber) + " events" << endl;
	for (int i = 0; i < comments.size(); i++)
	{
		cout << comments[i] << endl;
	}
	cout << "There are " + to_string(organisms.size()) + " alive" << endl;
	cout << "---------------------------" << endl;
	comments.clear();

	cout << "Click 'n' for next turn, click 'x' to finish simulation" << endl;
}

void World::newTurn() {

	for (int i = 0; i < organisms.size(); i++)
		organisms[i]->age++;

	sortOrganisms();

	if (this->turnNumber == 0)
		firstOrganisms();
	else
	{
		for (int i = 0; i < organisms.size(); i++)
		{
			this->organisms[i]->action();

			//checking if hasn't already died
			if (organisms.size() == i + 1)
			{
				//if it is Antelope it has a second move
				if (Antelope* v = dynamic_cast<Antelope*>(organisms[i]))
					this->organisms[i]->action();
			}
		}
	}
	turnNumber++;
	this->printBoard();
	this->addOrganisms();
}

//moving win organism and deleting losing organism
void World::moveAfterKill(Organism& killedOrganism, Organism& winOrganism, Organism& attacker){
	comments.push_back("Organism " + killedOrganism.draw() + " has been killed by Organism " + winOrganism.draw() + " at position x:" + to_string(winOrganism.getX()) + " y: " + to_string(winOrganism.getY()));
	if (&killedOrganism == &attacker)
	{
		board[killedOrganism.getX()][killedOrganism.getY()] = NULL;
	}
	else
	{
		board[killedOrganism.getX()][killedOrganism.getY()] = NULL;
		board[killedOrganism.getX()][killedOrganism.getY()] = &winOrganism;
		board[winOrganism.getX()][winOrganism.getY()] = NULL;
		winOrganism.setCoordinates({ winOrganism.getNewX(),winOrganism.getNewY() });
	}
}

void World::kill(Organism& killedOrganism, Organism& winOrganism, Organism& attacker) {

	for (int i = 0; i < organisms.size(); i++)
	{
		if (organisms[i] == &killedOrganism)
		{
			if (&attacker == &killedOrganism)
			{
				if (Plant* v = dynamic_cast<Plant*>(&winOrganism))
				{
					moveEatPlant(killedOrganism,winOrganism);
					for (int p = 0; p < organisms.size(); p++)
					{
						if(organisms[p] == &winOrganism)
							organisms.erase(organisms.begin() + p);
					}		
				}
				else
					moveAfterKill(killedOrganism, winOrganism, attacker);
			}
			else
				moveAfterKill(killedOrganism, winOrganism, attacker);

			organisms.erase(organisms.begin() + i);
			break;
		}
	}
}

//move animal on the plave of eaten plant
void World::moveEatPlant(Organism& killedOrganism, Organism& winOrganism) {
	board[killedOrganism.getX()][killedOrganism.getY()] = NULL;
	board[winOrganism.getX()][winOrganism.getY()] = NULL;
}

//adding organisms which have spawned in last turn
void World::addOrganisms() {
	for (int i = 0; i < plantsToAdd.size(); i++)
	{
		cout << plantsToAdd[i]->draw() << endl;
		this->organisms.push_back(plantsToAdd[i]);
		this->board[plantsToAdd[i]->coordinates.x][plantsToAdd[i]->coordinates.y] = plantsToAdd[i];
	}
	plantsToAdd.clear();

	for (int i = 0; i < AnimalsToAdd.size(); i++)
	{
		cout << AnimalsToAdd[i]->draw() << endl;
		this->organisms.push_back(AnimalsToAdd[i]);
		this->board[AnimalsToAdd[i]->coordinates.x][AnimalsToAdd[i]->coordinates.y] = AnimalsToAdd[i];
	}
	AnimalsToAdd.clear();
}

void World::saveWorld() {
	ofstream file;
	file.open("world.txt");
	for (int i = 0; i < organisms.size(); i++)
	{
		file<<organisms[i]->OrgToString();
		file << "\n";
	}
	file.close();
}

//returning organism depending on given symbol
Organism* World::orgBySymbol(char symbol,int age,struct Coordinates coordinates) {
	if (symbol == '!')
		return new Wolf(coordinates, *this);
	else if (symbol == '@')
		return new Sheep(coordinates, *this);
	else if (symbol == '&')
		return new Fox(coordinates, *this);
	else if (symbol == '$')
		return new Antelope(coordinates, *this);
	else if (symbol == '#')
		return new Turtle(coordinates, *this);
	else if (symbol == '?')
		return new Human(coordinates, *this);
	else if (symbol == 'G')
		return new Grass(coordinates, *this);
	else if (symbol == 'S')
		return new SowThistle(coordinates, *this);
	else if (symbol == 'U')
		return new Belladonna(coordinates, *this);
	else if (symbol == 'g')
		return new Guarana(coordinates, *this);
	else if (symbol == 'H')
		return new Hogweed(coordinates, *this);
	else return NULL;

}

void World::clearBoard() {

	board.clear();

	for (int i = 0; i < height; i++)
	{
		board.push_back(vector<Organism*>());

		for (int k = 0; k < width; k++)
			this->board[i].push_back(NULL);
	}
}

void World::loadWorld() {

	ifstream file;
	file.open("world.txt");

	clearBoard();
	organisms.clear();

	while (!file.eof())
	{
		char symbol;
		int  age;
		Coordinates loadCoordinates;
		file >> symbol;
		file >> age;
		file >> loadCoordinates.x;
		file >> loadCoordinates.y;
		Organism* newOrg = orgBySymbol(symbol, age, loadCoordinates);
		if (Human* v = dynamic_cast<Human*>(newOrg))
		{
			Human* org = dynamic_cast<Human*>(newOrg);

			int special;
			file >> special;
			org->setSpecialAbility(special);

			int special_cooldown;
			file >> special_cooldown;
			org->setSpecialCooldown(special_cooldown);

			this->board[loadCoordinates.x][loadCoordinates.y] = org;
			org->age = age;
			organisms.push_back(org);
		}
		else
		{
			this->board[loadCoordinates.x][loadCoordinates.y] = newOrg;
			newOrg->age = age;
			organisms.push_back(newOrg);
		}
	}
	system("CLS");
	this->printBoard();
}
