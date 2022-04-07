#include<iostream>
#include "World.h"
#include "Everything.h"

using namespace std;

int main()
{
	World* world = new World(20,20);

	for (int i = 0; i < 5; i++)
	{
		world->newTurn();
		world->printBoard();
	}
	

	return 0;
}