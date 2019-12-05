#include "JOS.h"
#include "Desktop.h"

Desktop::Desktop() : Window( "Desktop", 0, 0, JOS.W, JOS.H)
{
	//제목 표시줄
	titleBar = Box(JOS.W,3,true,1,1);
	titleBar.SetMaxTextLen(JOS.W-2);
	titleBar.SetText( name );
	titleBar.fill = true;

	//프로그램 아이콘들을 담을 상자
	apps = Box(JOS.W, 10, false, 1,0);
	apps.SetMaxTextLen((JOS.W-2)*5);
	apps.SetText("1.Finder 2.Editor 3.Calculator 4.Calendar 5.Games");
	apps.pos.y = JOS.H-6;
}
Desktop::~Desktop()
{

}
void Desktop::Update()
{
	apps.Update();
	titleBar.Update();
	box.Update();
}
void Desktop::Render()
{
	apps.Render(true);
	titleBar.Render(true);
	box.Render();
}
