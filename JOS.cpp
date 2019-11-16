#include "JOS.h"
#include "WindowManager.h"
#include "Desktop.h"

Texell g_backBuffer[SIZEY+1][SIZEX+1];
WindowManager windowManager;		// singleton 패턴 적용 요망
JOS_SYSTEM JOS;				// singleton 패턴 적용 요망, 운영체제 관리자 역활을 함

int main()
{
	bool _mainLoop = true;
	
	Box tempBox(12,3,true,1,1);
	tempBox.SetText("");

	//System Init
	JOS.Init();
	windowManager.Init();
	windowManager.AddWindow( new Desktop());
	
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
		JOS.SetTextBgColor(30,47);
		++JOS.frame;

		//do something in this frame
		windowManager.Update();
		if(Kbhit() == true)
			_mainLoop = false;

		//render
		windowManager.Render();

		for( int i = 0 ; i < SIZEY ; ++i)
		{
			JOS.SetDefaultColor();
			for(int j = 0 ; j <= SIZEX-1 ; ++j)
				g_backBuffer[i][j].Print();
				
				//g_backBuffer[i][j][0] == 0 ? printf(" ") : printf("%s",g_backBuffer[i][j]);
		
			printf("\033[%d;%dm\n", 0, 0);
		}
	
		if( _mainLoop == false )
			break;		
		//waiting
		sleep(1);
	}
	printf("\033[%d;%dm", 0, 0);
	
	cout<<"JOS IS END"<<endl;
	return 0;
}
// 화면에 특정 문자를 특정 위치에 출력, 조만간 텍셀이라는 구조체를 만들 예정
void Draw(int _x, int _y, const char * _c)
{
	if( !SetValidPos(&_x,&_y) )
		return ;
	g_backBuffer[_y][_x].SetText(_c);	
//        strcpy(g_backBuffer[_y][_x],_c);
//       g_backBuffer[_y][_x][3] = '\0';
}
void Draw(int _x, int _y, char * _c)
{
	if( !SetValidPos(&_x,&_y) )
		return ;
	g_backBuffer[_y][_x].SetText(_c);	
//      strcpy(g_backBuffer[_y][_x],_c);
//      g_backBuffer[_y][_x][3] = '\0';
}
void Draw(int _x, int _y, char _c)
{
	if( !SetValidPos(&_x,&_y) )
		return ;
	g_backBuffer[_y][_x].SetText(_c);	
//        char temp[4];
//        temp[0] = _c;
//        strcpy(g_backBuffer[_y][_x],temp);
//        g_backBuffer[_y][_x][1] = '\0';
}
// 키보드 버퍼가 비어있지 않으면 1을 반환
int Kbhit()
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
