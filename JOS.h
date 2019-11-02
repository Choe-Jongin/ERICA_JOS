#pragma once

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

bool SetValidPos(int * _x, int * _y)
{
	int x = *_x;
	int y = *_y;
	if( *_x < 0 )
		*_x = 0;
	if( *_x > SIZEX -1 )
		*_x = SIZEX -1;
	if( *_y < 0 )
		*_y = 0;
	if( *_y > SIZEY -1 )
		*_y = SIZEY -1;
	
	return (x==*_x)&&(y==*_y);
}
void Draw(int _x, int _y, const char * _c)
{
	if( !SetValidPos(&_x,&_y) )
		return ;
        strcpy(g_backBuffer[_y][_x],_c);
        g_backBuffer[_y][_x][3] = '\0';
}

void Draw(int _x, int _y, char * _c)
{
	if( !SetValidPos(&_x,&_y) )
		return ;
        strcpy(g_backBuffer[_y][_x],_c);
        g_backBuffer[_y][_x][3] = '\0';
}
void Draw(int _x, int _y, char _c)
{
	if( !SetValidPos(&_x,&_y) )
		return ;
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

