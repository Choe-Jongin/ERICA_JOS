#pragma once

#include <iostream>
#include <string.h>
#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


#define SIZEX 144 	// 최상위 윈도우 사이즈
#define SIZEY 36	// 최상위 윈도우 사이즈

using namespace std;


extern char g_backBuffer[SIZEY+1][SIZEX+1][4];	// 후면버퍼

//화면 밖을 벗어나는 좌표가 들어오면 값을 화면 안으로 수정하고 거짓을 반환
extern bool SetValidPos(int * _x, int * _y);
// 화면에 특정 문자를 특정 위치에 출력, 조만간 텍셀이라는 구조체를 만들 예정
extern void Draw(int _x, int _y, const char * _c);
extern void Draw(int _x, int _y, char * _c);
extern void Draw(int _x, int _y, char _c);
// 키보드 버퍼가 비어있지 않으면 1을 반환
extern int Kbhit(void);
// 윈도우 있는 Kbhit 함수를 쓸수 없어서 구글에서 검색해서 사용함 출처 >> https://corsa.tistory.com/18 [CORSA]
extern void Gotoxy(int x, int y);
