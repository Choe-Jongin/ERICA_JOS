#pragma once

#include <string>

class Position
{
	public:

	int x, y;
	Position( int _x = 0, int _y = 0)
	{
		this->x = _x;
		this->y = _y;
	}
	~Position()
	{

	}
	void SetX(int _x)
	{
		this->x = _x;
	}
	void SetY(int _y)
	{
		this->y =_y;
	}
	void SetXY(int _x, int _y)
	{
		this->x = _x;
		this->y = _y;
	}
};

class Object
{
	public:

	std::string type;
	Position pos;
		
	Object(char * _type)
	{
		type.assign(_type);
	}
	Object(int _x, int _y, char * _type)
	{
		pos.SetXY(_x,_y);
		type.assign(_type);
	}
	~Object(){}
	virtual	void Update(){}
	virtual void Render(){}

	void SetX(int _x)
        {
                pos.x = _x;
        }
        void SetY(int _y)
        {
                pos.y =_y;
        }
        void SetXY(int _x, int _y)
        {
                pos.x = _x;
                pos.y = _y;
        }

};
