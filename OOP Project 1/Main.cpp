#include<iostream>
#include "World.h"
#include "Everything.h"

using namespace std;

int main()
{
	srand(time(0));
	
	cout << "World Simulation by Wiktor Wysocki 188628" << endl;
	cout << "Click 'n' for next turn, click 'x' to finish simulation" << endl;
	
	string command;
	World world(25, 25);

	/*while(cin>>command)
	{
		if (command == "n")
			world.newTurn();
		else if (command == "x")
			break;
	}*/
	for(int i=0;i<100;i++)
		world.newTurn();
	
	
	return 0;
}