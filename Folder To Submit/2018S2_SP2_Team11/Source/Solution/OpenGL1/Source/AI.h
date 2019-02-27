#ifndef AI_H
#define AI_H

#include "Vehicle.h"

class AI : public Vehicle
{
public:
	AI();
	~AI();

	void SetNewLocation(Vector3);
	Vector3 GetNewLocation();

	bool ReDirect(Vector3 prevPos);
	int GetReCount();

	void CalcAngle();
	void SetNextForward(Vector3);
	bool CheckToMove(); //temporary
	int SetDir();
	bool IfTurn();
	virtual void RollFront(float u, float v, float angle, double dt);
	virtual void RollBack(float u, float v, double dt);

private:
	bool first;
	int reCount;
	bool detected;
	bool turn;
	bool brakeState;
	bool redirect;
	Vector3 nextForward;
	Vector3 rotation;
	Vector3 newPosition;
	Vector3 prevPos;
};
#endif
