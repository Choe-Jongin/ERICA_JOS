#include "JOS.h"
#include "Desktop.h"

Desktop::Desktop()
{
	Object("Window");
	Window( "Desktop", 0, 0, SIZEX, SIZEY);
}
Desktop::~Desktop()
{

}
void Desktop::Update()
{
	box.Update();
}
void Desktop::Render()
{
	box.Render();
}
