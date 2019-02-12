#ifndef PAINTABLE_H
#define PAINTABLE_H

#include "GameObject.h"

class Paintable : public GameObject
{
public:
	Paintable();

	void ChangeColor();

	~Paintable();
private:
};

#endif // !PAINTABLE_H
