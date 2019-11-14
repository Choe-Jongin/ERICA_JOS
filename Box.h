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

	//_w:넓이, _h:높이, _sh:테두리 출력 유무, _wall:글자 가로 정렬, _h:글자 세로 정렬
	Box(int _w = 10, int _h = 3, bool _sh = true,  int _wali = 0, int _hali = 0);
	~Box();
	void Update();
	void Render();
	void SetMaxTextLen(int _mtl)
	{	
		maxTextLen = _mtl;
	}
	void SetText( const char * _text )
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
