#include "JOS.h"
#include "Desktop.h"

Desktop::Desktop() : Window( "Desktop", 0, 0, JOS.W, JOS.H)
{
	titleBar = Box(JOS.W,3,true,1,1);
	titleBar.SetMaxTextLen(JOS.W-2);
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
