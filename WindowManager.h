#pragma once

#include "Window.h"

class WindowManager
{
public:

	list<Window*> windows;


	WindowManager(){}
	~WindowManager()
	{
		windows.clear();
	}
	void Init()
	{

	}

	void AddWindow( Window * _newWindow )
	{
		windows.push_back( _newWindow );		
	}
	void Update()
	{
		if( windows.size() <= 0 )
			return ;

		for( auto it = windows.begin() ; it != windows.end() ;  )
		{
			(*it) -> Update();
			if( (*it) -> isDelete )
				it = windows.erase(it);
			else
				++it;
		}
	}

	void Render()
	{
		if( windows.size() <= 0 )
			return ;
		
		for( auto it = windows.begin() ; it != windows.end() ; ++it  )
			(*it)-> Render();
	}


};
