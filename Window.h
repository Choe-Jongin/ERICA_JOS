#pragma once
#include "Box.h"

class Window : public Object
{
	public :

	Box box;

	int *x;
	int *y;
	int *width;
	int *height;
	string name;

	Window( const char * _name = "Window", int _x = 0, int _y = 0, int _w=10, int _h =3):Object("Window")
	{
		name.assign(_name);
		box.pos.x = _x;
		box.pos.y = _y;
		box.width = _w;
		box.height= _h;
		
		x = &(box.pos.x);
		y = &(box.pos.y);
		width = &(box.width);
		height = &(box.height);		
	}
	~Window(){}

	void Init( char * _name, int _x = 0, int _y = 0, int _w=10, int _h =3)
	{
		name.assign(_name);
		box.pos.x = _x;
		box.pos.y = _y;
		box.width = _w;
		box.height= _h;
		
		x = &(box.pos.x);
		y = &(box.pos.y);
		width = &(box.width);
		height = &(box.height);
	}
	virtual	void Update(){}
	virtual void Render(){}
};
