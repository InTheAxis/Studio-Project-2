#ifndef LOADSCENEBUTTON_H
#define LOADSCENEBUTTON_H
#include "Button.h"


class LoadSceneButton : public Button
{
public:
	LoadSceneButton();
	~LoadSceneButton();

	virtual void DoAction();
	virtual void AnimateButton();
private:

};

#endif
