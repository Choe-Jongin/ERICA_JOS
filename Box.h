#pragma once

#include "Object.h"

class Box : public Object
{
public:
	int width;
	int height;
	int walign;	// 0: left, 1: mid, 2; right;
	int halign;	// 0: top, 1: center, 2: bottom
	bool showFrame;
	
	std::string text;
	int maxTextLen;

	Box(int _w = 10, int _h = 3, bool _sh = true,  int _wali = 0, int _hali = 0): Object("Box")
	{
		this->width = _w;
		this->height = _h;
		showFrame = _sh;	
		maxTextLen = _w;
		walign = _wali;
		halign = _hali;
	}
	~Box(){}
	void Update()
	{

	}
	void Render()
	{
		if( showFrame == true )
		{
			
			for( int i = pos.x ; i < pos.x + width ; ++i)
        	        {
               	         	Draw(i,pos.y,"─");
               	        	Draw(i,pos.y + height,"─");
               		 }
		
	                for( int i = pos.y ; i < pos.y + height; ++i)
	                {
	                        Draw(pos.x,i,"│");
	                        Draw(pos.x + width,i,"│");
       		        }
       	         	Draw(pos.x, pos.y,"┌");
       	      		Draw(pos.x + width, pos.y,"┐");
       	         	Draw(pos.x,pos.y + height,"└");
       	 	        Draw(pos.x + width, pos.y + height,"┘");
		}
		
		if( text.size() > maxTextLen)
			text.erase(maxTextLen,text.size());

		for( int i = 0; i < height-2 ; ++i )
		{
			for( int j = 0 ; j < width-2 ; ++j )
			Draw(pos.x + j + 1, pos.y + i + 1, text[i*j + j]); 
		}

	}
	void SetMaxTextLen(int _mtl)
	{	
		maxTextLen = _mtl;
	}
	void SetText( char * _text )
	{
		text.assign(_text);
	}
	bool SetAlign( int _w = 1, int _h = 1)
	{
		if( _w > 3 || _h > 3 )
			return false;

		if( _w >= 0 )
			walign = _w;
		if( _h >= 0 )
			halign = _h;
	}
};
