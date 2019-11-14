#include "JOS.h"
#include "Box.h"

Box::Box(int _w, int _h, bool _sh, int _wali, int _hali)
{
	Object("Box");
	this->width = _w;
	this->height = _h;
	showFrame = _sh;
	maxTextLen = _w;
	walign = _wali;
	halign = _hali;
}
Box::~Box()
{

}
void Box::Update()
{

}
void Box::Render()
{
	if( showFrame == true )
	{
		for( int i = pos.x ; i < pos.x + width ; ++i)
		{
			Draw(i,pos.y,"─");
			Draw(i,pos.y + height - 1,"─");
		 }

		for( int i = pos.y ; i < pos.y + height -1; ++i)
		{
			Draw(pos.x,i,"│");
			Draw(pos.x + width -1,i,"│");
		}
		Draw(pos.x, pos.y,"┌");
		Draw(pos.x + width-1, pos.y,"┐");
		Draw(pos.x,pos.y + height-1,"└");
		Draw(pos.x + width-1, pos.y + height-1,"┘");
	}

	if( text.size() > maxTextLen)
		text.erase(maxTextLen,text.size());

	for( int i = 0; i < height-2 ; ++i )
	{
		int k = 0;
	      	if( walign == 0) k = 0;
		else if( walign == 1) k = (width-text.size())/2;
		else if( walign == 2) k = width - text.size()-2;
		for( int j = 0; j < width-2 ; ++j )
		{
			if( i*j + j >= text.size())
				break;
			Draw(pos.x + j + 1 + k, pos.y + i + 1, text[i*j + j]);
		}
	}

}
