#pragma once

#include "Window.h"


class Desktop : public Window
{
public:
	Box titleBar;
	Box apps;

	Desktop();
	~Desktop();

	void Update();
	void Render();
};
