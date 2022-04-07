#pragma once
#include<iostream>
#include <vector>
#include "World.h"

using namespace std;

struct Coordinates {
	int x, y;
};

class World;

class Organism{
protected:
	Coordinates coordinates;
	World* world;
	int strength, initiative;
	int age = 0;
public:
	Organism();
	Organism(int givenX, int givenY,World* givenWorld);
	
	virtual void action() =0;
	virtual void collision() = 0;
	virtual char draw() = 0;

	//getters
	int getStrength() { return this->strength; };
	int getX();
	int getY();

	virtual ~Organism();
};

class Cell : public Organism {
public:
	using Organism::Organism;
	void action();
	void collision();
	char draw();
	~Cell();
};

class Animal : public Organism {
	int newX, newY;
public:
	Animal();
	Animal(int givenX, int givenY, World* givenWorld);
	void action() override;
	void collision() override;
};

class Wolf : public Animal {
public:
	Wolf(int givenX, int givenY, World* givenWorld);;
	Wolf();
	char draw();
};

