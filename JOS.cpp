#include "JOS.h"
#include "WindowManager.h"
#include "Desktop.h"

Texell **g_backBuffer = NULL;
WindowManager windowManager;		// singleton 패턴 적용 요망
JOS_SYSTEM JOS;				// singleton 패턴 적용 요망, 운영체제 관리자 역활을 함

int main( int argc, char * argv[] )
{
	JOS.SetResolution( SIZEX, SIZEY );

	if( argc > 1 )
	{
		//테스트 모드로 실행
		if( strcmp(argv[1],"test") == 0 )
		{
			JOS.mode = 1;	
			--argc;
			for( int i = 1 ; i <= argc ; ++i )
				argv[i] = argv[i+1];
		}
	}

	if( argc > 2 )
	{
		int size1 = strlen( argv[1] );
		int size2 = strlen( argv[2] );
		//해상도를 설정한 채 실행
		if( size1 == 3 && size2 == 2 )
		{
			int w = (argv[1][0]-'0')*100 +  (argv[1][1]-'0')*10 + (argv[1][2]-'0');
			int h = 			(argv[2][0]-'0')*10 + (argv[2][1]-'0');
			if( w > 192 || h < 15 || h > 54 )
				JOS.errorlist.push_back(ERROR("해상도 범위 이상"));
			else 
				JOS.SetResolution( w, h );
		}
	}
	
	bool _mainLoop = true;
	
	Box tempBox(12,3,true,1,1);
	tempBox.SetText("");

	//System Init
	JOS.Init();
	windowManager.Init();
	windowManager.AddWindow( new Desktop());
	
	system("clear");

	//Main Loop
	while( _mainLoop )
	{	
		//flush backbuffer
		JOS.UpdateTime();
		
		while(Kbhit() == true)
		{
			char in = getchar();
			if( in  == 'q' )
				_mainLoop = false;
		}
	
		if( JOS.tickInFrame >= ONESEC/FPS )
		{
			JOS.SetTextBgColor(30,47);
			++JOS.frame;
			JOS.tickInFrame -= ONESEC/FPS;
			
			//do something in this frame
			windowManager.Update();
			
			//render
			JOS.InvalidRect(0,0,JOS.W,JOS.H);
			windowManager.Render();

			system("clear");
			for( int i = 0 ; i < JOS.H ; ++i)
			{
				JOS.SetDefaultColor();
				for(int j = 0 ; j < JOS.W ; ++j)
					g_backBuffer[i][j].Print();
				
				cout<<"\033[0;0m"<<endl;	
			}
			
			if( JOS.mode == 1 )
			{
				for( int i = 0 ; i < JOS.W ; ++i)
					std::cout<<'-';
				cout<<endl<<"frame:"<<JOS.frame<<"  "<<"RunTime: "<<JOS.hour<<":"<<JOS.min<<":"<<JOS.sec<<endl;
				cout<<"ErrorMessage:";
				for( auto it = JOS.errorlist.begin() ; it != JOS.errorlist.end() ; )
				{
					string s = it->message;
					cout<<s.c_str()<<", ";
					if( it->IsDelete(ONESEC/FPS) )
						it= JOS.errorlist.erase(it);
					else ++it;
				}
				cout<<endl;
			}

			//waiting
		}
		if( _mainLoop == false )
			break;		
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
}
void Draw(int _x, int _y, char _c)
{
	if( !SetValidPos(&_x,&_y) )
		return ;
	g_backBuffer[_y][_x].SetText(_c);	
}
void Draw(int _x, int _y, Texell texell)
{
	if( !SetValidPos(&_x,&_y) )
                return ;
        g_backBuffer[_y][_x] = texell;
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
	if( *_x > JOS.W -1 )
		*_x = JOS.W -1;
	if( *_y < 0 )
		*_y = 0;
	if( *_y > JOS.H -1 )
		*_y = JOS.H -1;
	
	return (x==*_x)&&(y==*_y);
}
