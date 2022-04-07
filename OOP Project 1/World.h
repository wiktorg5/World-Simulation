#pragma once
#include<iostream>
#include <vector>
#include "Everything.h"

using namespace std;

class Organism;

class World {
	int width, height;
	vector<Organism*> organisms;
	int turnNumber = 0;
public:
	vector< vector< Organism* > > board;

	World(int widthGiven, int heightGiven);
	void firstOrganisms();
	void printBoard();
	void newTurn();
	void moveAfterKill(Organism* killedOrganism, Organism* winOrganism);
	void kill(Organism* killedOrganism, Organism* winOrganism);

	int getWidth();
	int getHeight();
};