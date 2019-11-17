#pragma once

#include <iostream>

class Texell
{
public:

	char text[4];
	Texell()
	{
		text[0]=0;
		text[1]=0;
		text[2]=0;
		text[3]=0;
	}

	~Texell()
	{
		
	}

	void SetText( const char * _txt )
	{
		char * _tx = text;
		while(*_txt) {
			*_tx = *_txt;
			++_tx;++_txt;
		};
		*_tx = '\0';
	}

	void SetText( char _txt )
	{	
		text[0] = _txt;
		text[1] = '\0';
		text[2] = '\0';
		text[3] = '\0';
	}

	void Print()
	{
		if( text[0] == 0 )
			std::cout<<" ";
		else
			std::cout << text;
	}
	void Clear()
	{
		text[0] = text[1] = text[2] = text[3] = 0;
	}

};
