#ifndef CURSOR_H
#define CURSOR_H

#include <vector>
#include "Scene.h"
#include "LoadSceneButton.h"
#include <iostream>


class Cursor : public GameObject
{
public:
	Cursor();
	~Cursor();

	void SetOrthSize(Vector3);
	void Move(double dt);
	void CheckHover();	
	void SetAllButton(std::vector<Button*> allButtons);
	Button* GetButton(int index);
	void ResetMousePos();

private:
	Vector3 prevCursorXY, currentCursorXY;
	Vector3 deltaPosCursor;
	const float MOUSE_SENS = 0.1f;
	Vector3 orthSize;
	std::vector<Button*> allButtons;
	int totalbuttons;
	const float button_Xrange=6;
	const float button_Yrange = 2;
};

#endif
