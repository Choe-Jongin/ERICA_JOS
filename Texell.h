#pragma once

#include <iostream>

class Texell
{
public:

	char text[4];
	char textColor;
	char backColor;
	
	Texell( char _text, char _textColor = 30, char _backColor = 47  )
	{
		for( int i = 0 ; i < 4 ; ++i )
			text[i] = 0;
		text[0] = _text;
		textColor = _textColor;
		backColor = _backColor;
	
	}
	Texell( const char _text[4] = "", char _textColor = 30, char _backColor = 47  )
	{
		for( int i = 0 ; i < 4 ; ++i )
			text[i] = _text[i];
		textColor = _textColor;
		backColor = _backColor;
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

	void Print(char systxtcolor = 0, char sysbgcolor = 0 )
	{
		if( systxtcolor != textColor || sysbgcolor != backColor)
			printf("\033[%d;%dm", backColor, textColor);

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
