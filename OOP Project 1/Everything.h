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
	friend class World;
protected:
	World& world;
	Coordinates coordinates;
	int strength, initiative;
	int age = 0;
	Coordinates newCoordinates;
	vector<Coordinates> arrComb = { {0,1},{1,0},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1} };
public:
	Organism(Coordinates coordinates,World& world);
	
	virtual void action() =0;
	virtual void collision() = 0;
	virtual string draw() = 0;
	//virtual Organism* makeCopy(Coordinates coordinates) = 0;

	//setters
	void setCoordinates(Coordinates newCoordinates);
	//getters
	int getStrength() { return this->strength; };
	int getX();
	int getY();
	int getNewX();
	int getNewY();
	Coordinates getCoordinates();
	Coordinates makeNewXYToSow(Coordinates coordinates);

	virtual ~Organism();
};

class Animal : public Organism {
public:
	vector<Coordinates> arrComb = { {0,1},{1,0},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1} };

	Animal(Coordinates coordinates,World& world);
	void action() override;
	void collision() override;
	void basicCollision();
	void breeding(Organism* secondAnimal);
	Coordinates makeNewXY(Coordinates coordinates);
	void breedBasic(Coordinates newOrganismCoordinates);
	virtual Organism* breedCopy(Coordinates coordinates) { return 0; };
};

class Wolf : public Animal {
public:
	Wolf(Coordinates coordinates, World& world);
	string draw();
	Organism* breedCopy(Coordinates coordinates);
};

class Sheep : public Animal {
public:
	Sheep(Coordinates coordinates, World& world);
	string draw();	
	Organism* breedCopy(Coordinates coordinates);
};

class Fox : public Animal {
public:
	Fox(Coordinates coordinates, World& world);
	string draw();
	Coordinates makeNewXY(Coordinates coordinates);
	Organism* breedCopy(Coordinates coordinates);
};

class Turtle : public Animal {
public:
	Turtle(Coordinates coordinates, World& world);
	string draw();
	Organism* breedCopy(Coordinates coordinates);
};

class Antelope : public Animal {
public:
	Antelope(Coordinates coordinates, World& world);
	string draw();
	void backFromFight(Antelope* org);
	Coordinates makeNewXYAfterFight(Coordinates coordinates);
	Organism* breedCopy(Coordinates coordinates);
};

class Plant : public Organism {
protected:
	int sowTries = 1;
public:
	Plant(Coordinates coordinates, World& world);
	vector<Coordinates> arrComb = { {0,1},{1,0},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1} };

	void action() override;
	void collision() override;
	virtual Organism* sowCopy(Coordinates coordinates);
};

class Grass : public Plant {
public:
	Grass(Coordinates coordinates, World& world);
	string draw();
	Organism* sowCopy(Coordinates coordinates) override;
};

class SowThistle : public Plant {
public:
	SowThistle(Coordinates coordinates, World& world);
	string draw();
	Organism* sowCopy(Coordinates coordinates) override;
};

class Guarana : public Plant {
public:
	Guarana(Coordinates coordinates, World& world);
	string draw();
	Organism* sowCopy(Coordinates coordinates) override;
};

class Belladonna : public Plant {
public:
	Belladonna(Coordinates coordinates, World& world);
	string draw();
	Organism* sowCopy(Coordinates coordinates) override;
};

class Hogweed : public Plant {
public:
	Hogweed(Coordinates coordinates, World& world);
	string draw();
	Organism* sowCopy(Coordinates coordinates) override;
	void action();
};

class Human : public Animal {
	bool special_ability = false;
	Coordinates newCoordinates;
public:
	Human(Coordinates coordinates, World& world);
	void action();
	void changeHumanPosition();
	string draw();
	bool checkCoordinates(int direction);
	void purification();
};

