#include "JOS.h"
#include "WindowManager.h"
#include "Desktop.h"

WindowManager WindowManager;		// singleton 패턴 적용 요망
int main()
{
	char g_backBuffer[SIZEY+1][SIZEX+1][4] = {0};
	bool _mainLoop = true;
	int _frame = 0;
	
	Box tempBox(12,3,true,1,1);
	tempBox.SetText("");

	//System Init
	WindowManager.Init();
//	WindowManager.AddWindow( new Window("Desktop",0,0,SIZEX,SIZEY));
	WindowManager.AddWindow( new Desktop());
	
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
		memset(g_backBuffer,0,sizeof(g_backBuffer));
		system("clear");
	
		/*
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
		*/

		WindowManager.Update();

		//do something in this frame
		if(Kbhit() == true)
			_mainLoop = false;
	

		++_frame;
		
		int _tempframe = _frame;
		char _strframe[11];
		for( int i = 0 ; i < 10 ; ++i )
		{
			_strframe[9-i] = '0' + _tempframe%10;
			_tempframe/=10;

			Draw(SIZEX/2+5-i,SIZEY/2,_strframe[9-i]);
		}
		_strframe[10] = '\0';
		tempBox.SetText(_strframe);
		tempBox.SetX(SIZEX/2);
		tempBox.pos.y += 1;

		//render
		WindowManager.Render();
		tempBox.Render();
		for( int i = 0 ; i < SIZEY ; ++i)
		{
			for(int j = 0 ; j <= SIZEX-1 ; ++j)
				g_backBuffer[i][j][0] == 0 ? printf(" ") : printf("%s",g_backBuffer[i][j]);
		
			printf("\n");
		}
		
		//waiting
		sleep(1);
	}
	
	cout<<"JOS IS END"<<endl;
	return 0;
}
//화면 밖을 벗어나는 좌표가 들어오면 값을 화면 안으로 수정하고 거짓을 반환
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
// 화면에 특정 문자를 특정 위치에 출력, 조만간 텍셀이라는 구조체를 만들 예정
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
// 키보드 버퍼가 비어있지 않으면 1을 반환
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
