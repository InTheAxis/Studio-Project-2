#include "CollectibleSpeedBoost.h"

CollectibleSpeedBoost::CollectibleSpeedBoost()
{
	pickedUp = false;
	maxActiveTime = 10.f;
	activeTime=0;
}

CollectibleSpeedBoost::~CollectibleSpeedBoost()
{
}

bool CollectibleSpeedBoost::CheckAbsorption(Vector3 objectLocation)
{
	/*std::cout << PickedUp << std::endl;*/
	if (!pickedUp)
	{
		bool Xwithin = false;
		bool Zwithin = false;

		//checks if objects is touching the PowerUp
		if (((objectLocation.x) <= translate.x + PICKUP_RANGE)
			&& ((objectLocation.x) >= translate.x - PICKUP_RANGE))
		{
			Xwithin = true;
		}

		else
			Xwithin = false;

		if (((objectLocation.z) <= translate.z + PICKUP_RANGE)
			&& ((objectLocation.z) >= translate.z - PICKUP_RANGE))
		{
			Zwithin = true;
		}

		else
			Zwithin = false;

		// if object is touching powerup
		if (Xwithin && Zwithin)
		{
			pickedUp = true;
			activeTime = maxActiveTime;
			return true;
		}

	}
		
	else
		return false;

}

void CollectibleSpeedBoost::ApplyEffect(GameObject *object,double dt)
{
	std::cout << activeTime << std::endl;
	if (pickedUp)
	{
		activeTime -= dt;
		//add effect here
		/*object->IncrementTranslate(Vector3(0, 0, 0.25));*/

		if(activeTime<=0)
			pickedUp = false;
	}
	
	else
	{

	}
		
}




