#include "CollectibleSprayBoost.h"
#include "Paintable.h"

CollectibleSprayBoost::CollectibleSprayBoost()
{
	this->pickedUp = false;
	maxActiveTime = 10.f; //How many seconds for powerup
}

CollectibleSprayBoost::~CollectibleSprayBoost()
{
}

bool CollectibleSprayBoost::CheckAbsorption(Vector3 objectLocation)
{
	/*std::cout << PickedUp << std::endl;*/
	if (!pickedUp)
	{
		bool Xwithin = false;
		bool Zwithin = false;

		//checks if objects is touching the PowerUp
		if ((objectLocation.x <= (translate.x + PICKUP_RANGE)) && (objectLocation.x >= (translate.x - PICKUP_RANGE)))
		{
			Xwithin = true;
		}

		if ((objectLocation.z <= (translate.z + PICKUP_RANGE)) && (objectLocation.z >= (translate.z - PICKUP_RANGE)))
		{
			Zwithin = true;
		}

		// if object is touching powerup
		if (Xwithin && Zwithin)
		{
			this->pickedUp = true;
			/*activeTime = maxActiveTime;*/
		}
		else
		{

			this->pickedUp = false;
		}
	}
	return this->pickedUp;
}

void CollectibleSprayBoost::ApplyEffect(GameObject *object, double dt)
{
	if (pickedUp)
	{
		maxActiveTime -= dt;	

		if (maxActiveTime <= 0)
		{
			pickedUp = false;
			maxActiveTime = 10.f;
			translate.x = RandomNumberGenerator();
			translate.z = RandomNumberGenerator();
		}
	}
}

bool CollectibleSprayBoost::GetPickedUp()
{
	return this->pickedUp;
}


