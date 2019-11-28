#pragma once

#include <list>
#include <string.h>
#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include "Texell.h"

#define SIZEX 144 	// 최상위 윈도우 사이즈
#define SIZEY 36	// 최상위 윈도우 사이즈
#define FPS 30		// 최대 FPS

using namespace std;

extern Texell **g_backBuffer;	// 후면버퍼

//화면 밖을 벗어나는 좌표가 들어오면 값을 화면 안으로 수정하고 거짓을 반환
extern bool SetValidPos(int * _x, int * _y);
// 화면에 특정 문자를 특정 위치에 출력, 조만간 텍셀이라는 구조체를 만들 예정
extern void Draw(int _x, int _y, const char * _c);
extern void Draw(int _x, int _y, char _c);
extern void Draw(int _x, int _y, Texell texell);
// 키보드 버퍼가 비어있지 않으면 1을 반환
extern int Kbhit();
// 윈도우 있는 Kbhit 함수를 쓸수 없어서 구글에서 검색해서 사용함 출처 >> https://corsa.tistory.com/18 [CORSA]
extern void Gotoxy(int x, int y);


//시스템을 총괄하는 구조체, 딱 한번만 선언되어야 함
class JOS_SYSTEM
{
public:
	char textColor;	
	char backColor;
	int frame;
	int mode;
	int W,H; // 시스템 해상도
	
	clock_t currenttime;
	clock_t previoustime;
	unsigned int tick;
	unsigned int tickInFrame;

	list<string> errorlist;
	JOS_SYSTEM()
	{
		previoustime = clock();
		textColor = 30;
		backColor = 47;
		frame = 0;
		mode = 0; 	// 0:normal, 1:test
		
		W = SIZEX;
		H = SIZEY;
		
		currenttime = clock();
		tick = currenttime - previoustime;
		tickInFrame = 0;
	}
	~JOS_SYSTEM()
	{

	}
	//초기화
	void Init()
	{
		textColor = 30;
                backColor = 47;
		frame = 0;
	}
	//색 적용
	void ApplyColor()
	{
		printf("\033[%d;%dm", backColor, textColor);
	}
	//글자색 설정
	void SetTextColor(int _color)
	{
		if( textColor == _color )
			return ;
		textColor = _color;
		ApplyColor();
	}
	//배경색 설정
	void SetBackColor(int _color)
	{
		if( backColor == _color )
			return ;
		backColor = _color;
		ApplyColor();
	}
	//글자,배경색 동시 설정
	void SetTextBgColor(int _txt, int _bg)
	{
		if( textColor == _txt && backColor == _bg )
			return ;
		textColor = _txt;
		backColor = _bg;
		ApplyColor();
	}
	//기본 색상으로 설정
	void SetDefaultColor()
	{
		if( textColor == 30 && backColor == 47 )
			return ;
		textColor = 30;
                backColor = 47;
		ApplyColor();

	}
	//해상도 변경  음수:범위 미만, 양수:범위초과, 0 정상변경
	int SetResolution(int x, int y)
	{
		if( x < 100 ){
			errorlist.push_back("x is so low");
			return -1;
		}else if( y < 15 ){
			errorlist.push_back("y is so low");
			return -1;
		}else if( x > 192 ){
			errorlist.push_back("x is so high");
			return 1;
		}else if( y > 54 ){
			errorlist.push_back("y is so high");
			return 1;
		}
		
		if( g_backBuffer != NULL )
		{	
			for( int i = 0 ; i < H ; ++i )
				delete [] g_backBuffer[i];
			delete [] g_backBuffer;
		}

		g_backBuffer = new Texell*[y];
		for( int i = 0 ; i < y ; ++i )
			g_backBuffer[i] = new Texell[x];
		
		W = x;
		H = y;
	}
	void InvalidRect(int left, int top, int right,int bottom)
	{
		for( int i = top ; i < bottom ; ++i )
			for( int j = left ; j < right ; ++j )
				g_backBuffer[i][j].Clear();
	}
	void UpdateTime()
	{
		currenttime = clock();
                tick = currenttime-previoustime;
                previoustime = currenttime;
                tickInFrame += tick;
	}

};
extern JOS_SYSTEM JOS;
