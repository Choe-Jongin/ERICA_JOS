#include "JOS.h"
#include "Desktop.h"

Desktop::Desktop() : Window( "Desktop", 0, 0, SIZEX, SIZEY)
{
	titleBar = Box(SIZEX,3,true,1,1);
	titleBar.SetMaxTextLen(SIZEX-2);
	titleBar.SetText( name );
}
Desktop::~Desktop()
{

}
void Desktop::Update()
{
	titleBar.Update();
	box.Update();
}
void Desktop::Render()
{
	titleBar.Render();
	box.Render();
}
