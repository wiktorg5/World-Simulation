#pragma once
#include<iostream>
#include <vector>
#include "Classes.h"

using namespace std;

class Organism;

class World {
	int width, height;
	int turnNumber = 0;
	
public:
	vector< vector< Organism* > > board;
	vector<Organism*> organisms;
	vector<Organism*> plantsToAdd;
	vector<Organism*> AnimalsToAdd;
	vector<string> comments;

	World(int widthGiven, int heightGiven);
	void sortOrganisms();
	static bool compareOrganisms(Organism* org1, Organism* org2);
	void firstOrganisms();
	void printBoard();
	void newTurn();
	void moveAfterKill(Organism& killedOrganism, Organism& winOrganism, Organism& attacker);
	void kill(Organism& killedOrganism, Organism& winOrganism, Organism& attacker);
	Organism* getRandomOrganism(int x, int y);
	void addOrganisms();
	void moveEatPlant(Organism& killedOrganism, Organism& winOrganism);
	void saveWorld();
	void loadWorld();
	Organism* orgBySymbol(char symbol, int age,struct Coordinates coordinates);
	void clearBoard();

	int getWidth();
	int getHeight();
};