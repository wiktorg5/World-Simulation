#include "Classes.h"
#include<string>

Hogweed::Hogweed(Coordinates coordinates, World& world) : Plant(coordinates, world) {
	this->strength = 0;
};

string Hogweed::draw() {
	return "H";
}

Organism* Hogweed::sowCopy(Coordinates coordinates) {
	return new Hogweed(coordinates, this->world);
}

void Hogweed::action() {

	for (int i = 0; i < arrComb.size(); i++)
	{
		int newX = this->coordinates.x + arrComb[i].x;
		int newY = this->coordinates.y + arrComb[i].y;

		if (newX >= this->world.getWidth() || newX < 0 || newY >= this->world.getHeight() || newY < 0)
			continue;

		Organism* orgToKill = world.board[newX][newY];
		
		if (Animal* v = dynamic_cast<Animal*>(orgToKill))
		{
			world.board[orgToKill->getX()][orgToKill->getY()] = NULL;
			for (int i = 0; i < world.organisms.size(); i++)
			{
				if (world.organisms[i] == orgToKill)
				{
					world.organisms.erase(world.organisms.begin() + i);
				}
			}
			world.comments.push_back("Organism " + orgToKill->draw() + " has been killed by Organism " + this->draw() + " at position x:" + to_string(orgToKill->getX()) + " y: " + to_string(orgToKill->getY()));
		}
	}
}
