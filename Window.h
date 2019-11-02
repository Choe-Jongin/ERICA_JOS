#pragma once
#include "Object.h"
class Window : public Object
{
	
	public :



	Window():Object(0,0,"Window"){}
	~Window(){}

	void Update();
	void Render();	
};
