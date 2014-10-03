#include "User.h"
using namespace std;

User::User(string ID, string name)
{
	_name = name;
	_id = ID;
}

User::User (const User & other)
{
	_name = other.getName();
	_id = other.getID();
}

User::~User()
{
}

string User::getID () const
{
	return _id;
}

string User::getName () const
{
	return _name;
}

