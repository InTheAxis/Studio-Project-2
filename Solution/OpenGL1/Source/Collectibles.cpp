#include "Collectibles.h"

Collectibles::Collectibles()
{

}

Collectibles::~Collectibles()
{
}

float Collectibles::GetActiveTime()
{
	return activeTime;
}

void Collectibles::SetActiveTime()
{
	activeTime = maxActiveTime;
}



bool Collectibles::GetPickedUp()
{
	return pickedUp;
}

void Collectibles::SetPickedUp(bool PickedUp)
{
	this->pickedUp = PickedUp;
}

float Collectibles::RandomNumberGenerator()
{

	float number=0;
	srand(time(NULL));
	number = rand() % 100+(-50);

	return number;
}


