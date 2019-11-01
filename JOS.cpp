#include <iostream>
#include <locale.h>
#include <stddef.h>

#define SIZEX 40
#define SIZEY 11

using namespace std;

wchar_t  g_backBuffer[SIZEY+1][SIZEX+1];

void Draw(int _x, int _y, wchar_t _c)
{
	g_backBuffer[_y][_x] = _c;
}


void Gotoxy(int x, int y)
{
	printf("\033[%d;%df",y,x);
}

int main()
{

	//System Init
	system("clear");
	setlocale(LC_ALL,"");
	
	for( int y = 0 ; y < SIZEY ; ++y )
	{
	
		for( int x = 0 ; x < SIZEX ; ++x )
		{
			g_backBuffer[y][x] = L' ';

		}

		g_backBuffer[y][SIZEX] = L'\n';

	}


	//Main Loop
	while( true )
	{	
		//flush backbuffer
		system("clear");

		//do something in this frame
		for( int i = 0 ; i < SIZEX ; ++i)
		{
			Draw(i,0,L'─');
			Draw(i,SIZEY-1,L'─');
		}

		for( int i = 0 ; i < SIZEY ; ++i)
		{
			Draw(0,i,L'│');
			Draw(SIZEX-1,i,L'─');
		}
		Draw(0,0,L'┌');
		Draw(SIZEX-1,0,L'┐');
		Draw(0,SIZEY-1,L'└');
		Draw(SIZEX-1,SIZEY-1,L'┘');

		//render
//		wprintf(L"%s", g_backBuffer[0]);
		for( int i = 0 ; i < SIZEY ; ++i)
			for(int j = 0 ; j < SIZEX ; ++j)
	//			wprintf(L"%c",g_backBuffer[i][j]);
				;


//		wprintf(L"%c",L'─');
		break;
	}

	
	cout<<"JOS IS END"<<endl;
	cout<<"JOS IS END"<<endl;

//	Gotoxy(5,10);
//	cout << " Start the JOS! " << endl;
	return 0;
}
