#pragma once

#include "Window.h"


class Desktop : public Window
{
public:
	Box titleBar;
	Desktop();
	~Desktop();

	void Update();
	void Render();
};
