#pragma once

#include "Window.h"


class Desktop : public Window
{
public:
	Desktop();
	~Desktop();

	void Update();
	void Render();
};
