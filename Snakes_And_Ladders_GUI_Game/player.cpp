#include <iostream>
#include <string>
#include <cstring>

using namespace std;

#include "player.h"

Player::Player()
{
	_currency=0;
	_position=0;
	_job=10;
	_win=false;
}

void Player::label(string name, int job)
{
//	name[8]='\0';
	_name=name;
	_job=job;
}

void Player::addposition(int position)
{
	_position+=position;
}

void Player::setposition(int position)
{
	_position=position;
}

int Player::currentposition()
{
	return _position;
}

void Player::addcurrency(int currency)
{
	_currency+=currency;
}

void Player::subcurrency(int currency)
{ 	
	_currency-=currency;
}


int Player::currentcurrency()
{
	return _currency;
}

void Player::outputjob()
{
	if(_job==0) //Knight
	{
		cout << "@";
	}
	if(_job==1) //Robber
	{
		cout << "&";
	}
	if(_job==2) //Priest
	{
		cout << "+";
	}
	if(_job==3) //Magician
	{
		cout << "!";
	}
	if(_job==4) //Hunter
	{
		cout << "{";
	}
	if(_job==5) //Apparition
	{
		cout << "0";
	}
	if(_job==6) //Farmer
	{
		cout << "#";
	}
	if(_job==7) //Jester
	{
		cout << "%";
	}
	if(_job==8) //Pirate
	{
		cout << "R";
	}
	if(_job==9) //Snake
	{
		cout << "S";
	}
	if(_job==10)
	{
		cout << " ";
	}
}

int Player::outputjobindex()
{
	return _job;
}

void Player::outputname()
{
	cout << _name;
}

bool Player::checkvictory()
{
	if(_position==39)
	{
		_win=true;
	}
	return _win;
}
string Player::returnname()
{
	return _name;
}
