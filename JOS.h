#pragma once

#include <string.h>
#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "Texell.h"

#define SIZEX 144 	// 최상위 윈도우 사이즈
#define SIZEY 36	// 최상위 윈도우 사이즈

using namespace std;

extern Texell g_backBuffer[SIZEY+1][SIZEX+1];	// 후면버퍼

//화면 밖을 벗어나는 좌표가 들어오면 값을 화면 안으로 수정하고 거짓을 반환
extern bool SetValidPos(int * _x, int * _y);
// 화면에 특정 문자를 특정 위치에 출력, 조만간 텍셀이라는 구조체를 만들 예정
extern void Draw(int _x, int _y, const char * _c);
extern void Draw(int _x, int _y, char * _c);
extern void Draw(int _x, int _y, char _c);
// 키보드 버퍼가 비어있지 않으면 1을 반환
extern int Kbhit();
// 윈도우 있는 Kbhit 함수를 쓸수 없어서 구글에서 검색해서 사용함 출처 >> https://corsa.tistory.com/18 [CORSA]
extern void Gotoxy(int x, int y);


//시스템을 총괄하는 구조체, 딱 한번만 선언되어야 함
class JOS_SYSTEM
{
public:
	int textColor;	
	int backColor;
	int frame;
	int mode;
	int W,H; // 시스템 해상도
	JOS_SYSTEM()
	{
		textColor = 30;
		backColor = 47;
		frame = 0;
		mode = 0; 	// 0:normal, 1:test
		
		W = SIZEX;
		H = SIZEY;
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
		textColor = _color;
		ApplyColor();
	}
	//배경색 설정
	void SetBackColor(int _color)
	{
		backColor = _color;
		ApplyColor();
	}
	//글자,배경색 동시 설정
	void SetTextBgColor(int _txt, int _bg)
	{
		textColor = _txt;
		backColor = _bg;
		ApplyColor();
	}
	//기본 색상으로 설정
	void SetDefaultColor()
	{
		textColor = 30;
                backColor = 47;
		ApplyColor();

	}

};
extern JOS_SYSTEM JOS;
