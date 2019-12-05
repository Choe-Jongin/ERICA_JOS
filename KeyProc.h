#pragma once

#include <list>



class Key
{
public:
 	int value;
	int state;
	Key(int v, int s)
	{
		value = v;
		state = s; // 1: 눌림, 2: 지속적으로 눌림, 3: 땜
	}
};

class KeyProc
{

public:

	std::list<Key> inputs;

	void AddKey( int _value)
	{
		for( auto it = inputs.begin() ; it != inputs.end() ; ++it )
			if( it->value == _value )
				it->state = 2;
		inputs.push_back( Key(_value, 1) ); 
	}
	int IsPress( int _value )
	{
		for( auto it = inputs.begin() ; it != inputs.end() ; ++it )
			if( it->value == _value)
				if( it->state == 1 || it->state == 2 )
					return 1;
		return 0;
	}
	int IsPress( const char * _values )
	{
		int size = strlen(_values);
		for( auto it = inputs.begin() ; it != inputs.end() ; ++it )
		{
			for( int i = 0 ; i < size ; ++i )
				if( it->value == _values[i])
					if( it->state == 1 || it->state == 2 )
						return 1;
		}	
		return 0;
	}
	int GetKeyState( int _value )
	{
		for( auto it = inputs.begin() ; it != inputs.end() ; ++it )
			if( it->value == _value)
				return it->state;
		return 0;
	}
	void Update()
	{
		for( auto it = inputs.begin() ; it != inputs.end() ; )
		{
			if( it->state == 3 )
				it = inputs.erase(it);
			else
			{
				it->state = 3;
				++it;
			}
		}
	}

};
