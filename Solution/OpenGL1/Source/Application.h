#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

#define RESOLUTION_X _RESOLUTION_X
#define RESOLUTION_Y _RESOLUTION_Y

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);

	static double cursorX, cursorY;
	static bool rightMouseClick, leftMouseClick;
	const static int _RESOLUTION_X = 1080;
	const static int _RESOLUTION_Y = 720;
private:
	//Declare a window object
	StopWatch m_timer;
};

#endif