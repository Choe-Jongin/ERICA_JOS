#include <iostream>
#include <string.h>
#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZEX 160
#define SIZEY 45

using namespace std;

char  g_backBuffer[SIZEY+1][SIZEX+1][4];

void Draw(int _x, int _y, char * _c)
{
	strcpy(g_backBuffer[_y][_x],_c);
	g_backBuffer[_y][_x][3] = '\0';
}
void Draw(int _x, int _y, char _c)
{
	char temp[4];
	temp[0] = _c;
	strcpy(g_backBuffer[_y][_x],temp);
	g_backBuffer[_y][_x][1] = '\0';
}


int Kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}
// 윈도우 있는 Kbhit 함수를 쓸수 없어서 구글에서 검색해서 사용함 출처 > ㅑhttps://corsa.tistory.com/18 [CORSA]

void Gotoxy(int x, int y)
{
	printf("\033[%d;%df",y,x);
}

int main()
{
	bool _mainLoop = true;
	int _frame = 0;
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
	while( _mainLoop )
	{	
		//flush backbuffer
		system("clear");

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

		//do something in this frame
		if(Kbhit() == true)
			_mainLoop = false;
		
		++_frame;
		
		int _tempframe = _frame;
		char _strframe[10];
		for( int i = 0 ; i < 10 ; ++i )
		{
			_strframe[9-i] = '0' + _tempframe%10;
			_tempframe/=10;

			Draw(SIZEX/2+5-i,SIZEY/2,_strframe[9-i]);
		}
		
		

		//render
		for( int i = 0 ; i < SIZEY ; ++i)
			for(int j = 0 ; j <= SIZEX ; ++j)
				printf("%s",g_backBuffer[i][j]);

		
		//waiting
		sleep(1);
	}
	
	cout<<"JOS IS END"<<endl;

	return 0;
}
