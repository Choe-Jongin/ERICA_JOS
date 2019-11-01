#include <iostream>
#include <string.h>
#include <cstring>
#define SIZEX 160
#define SIZEY 45

using namespace std;

char  g_backBuffer[SIZEY+1][SIZEX+1][4];

void Draw(int _x, int _y, char * _c)
{
	strcpy(g_backBuffer[_y][_x],_c);
	g_backBuffer[_y][_x][3] = '\0';
}


void Gotoxy(int x, int y)
{
	printf("\033[%d;%df",y,x);
}

int main()
{

	//System Init
	system("clear");
	
	for( int y = 0 ; y < SIZEY ; ++y )
	{
		for( int x = 0 ; x < SIZEX ; ++x )
		{
			Draw(x,y," ");
		}

		Draw(SIZEX,y,"\n");
	}

	//Main Loop
	while( true )
	{	
		//flush backbuffer
		system("clear");

		//do something in this frame
		for( int i = 0 ; i < SIZEX ; ++i)
		{
			Draw(i,0,"─");
			Draw(i,SIZEY-1,"─");
		}

		for( int i = 0 ; i < SIZEY ; ++i)
		{
			Draw(0,i,"│");
			Draw(SIZEX-1,i,"│");
		}
		Draw(0,0,"┌");
		Draw(SIZEX-1,0,"┐");
		Draw(0,SIZEY-1,"└");
		Draw(SIZEX-1,SIZEY-1,"┘");
		Draw(0,SIZEY,"\0");
		//render
		for( int i = 0 ; i < SIZEY ; ++i)
			for(int j = 0 ; j <= SIZEX ; ++j)
				printf("%s",g_backBuffer[i][j]);

		break;
	}
	
	cout<<"JOS IS END"<<endl;

	return 0;
}
