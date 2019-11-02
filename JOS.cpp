#include "JOS.h"
#include "Box.h"

int main()
{
	bool _mainLoop = true;
	int _frame = 0;
	
	Box tempBox(12,3,true,1,1);
	tempBox.SetText("");

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
		memset(g_backBuffer,0,sizeof(g_backBuffer));
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
