#include "Everything.h"

Plant::Plant(Coordinates coordinates,World& world)
	: Organism(coordinates, world) {
	this->initiative = 0;
}

void Plant::action() {

	for (int i = 0; i < this->sowTries; i++)
	{
		int sowingProbability = rand() % 100;

		if (sowingProbability > 98)
		{
			Coordinates sowCoordinates = makeNewXYToSow(this->coordinates);

			if (sowCoordinates.x == this->coordinates.x && sowCoordinates.y == this->coordinates.y)
				return;
			else
			{
				Organism* newOrg = this->sowCopy(sowCoordinates);
				this->world.plantsToAdd.push_back(newOrg);
			}
		}
	}
}

void Plant::collision() {

}

Organism* Plant::sowCopy(Coordinates coordinates) { return 0; };