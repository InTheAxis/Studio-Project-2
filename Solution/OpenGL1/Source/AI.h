#ifndef AI_H
#define AI_H

#include "Vehicle.h"

class AI : public Vehicle
{
public:
	AI();
	~AI();

	void CalcAngle();
	void SetNextForward(Vector3);
	bool CheckToMove(); //temporary
	int SetDir();
	bool IfDetected();
	bool IfTurn();
	int CheckBrake();
	virtual void RollFront(float u, float v, float angle, double dt);
	virtual void RollBack(float u, float v, double dt);

private:
	int spotCount;
	bool detected;
	bool turn;
	bool brakeState;
	Vector3 nextForward;
	Vector3 rotation;
	Vector3 newPosition;
};
#endif
