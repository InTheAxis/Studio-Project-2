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
	return PickedUp;
}

void Collectibles::SetPickedUp(bool PickedUp)
{
	this->PickedUp = PickedUp;
}


