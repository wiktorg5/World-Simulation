#include<iostream>
#include "World.h"
#include "Everything.h"
#include<conio.h>

using namespace std;

#define N_SIGN 110
#define X_SIGN 120
#define S_SIGN 115
#define L_SIGN 108

int main()
{
	srand(time(0));
	
	string command;
	World world(25, 25);

	int input;

	cout << "World Simulation by Wiktor Wysocki 188628" << endl;
	cout << "Click 'n' for next turn, click 'x' to finish simulation" << endl;

	while(input=_getch())
	{
		cout << "World Simulation by Wiktor Wysocki 188628" << endl;
		cout << "Click 'n' for next turn, click 'x' to finish simulation" << endl;
		if (input == N_SIGN)
			world.newTurn();
		else if (input == X_SIGN)
			break;
		else if (input == S_SIGN)
			world.saveWorld();
		else if (input == L_SIGN)
			world.loadWorld();
	}
	
	
	
	return 0;
}