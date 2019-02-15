#ifndef SELECTOR_H
#define SELECTOR_H

#include <vector>
#include "Scene.h"
#include <iostream>


class Button : public GameObject
{
public:
	Button();
	~Button();

	bool GetOnClickEvent();
	void SetOnClickEvent(bool);
	void SetHover(bool hover);
	bool GetHover();

	virtual void DoAction() = 0;
	virtual void AnimateButton() = 0;
protected:
	bool hover;	// check if cursor hovering over button
	bool onClick; //if button is triggered

};

#endif
