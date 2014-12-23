#include "User.h"
using namespace std;

User::User(string ID, string name)
{
	_name = name;
	_id = ID;
	rentedmovie = NULL;
}

User::User (const User & other)
{
	_name = other.getName();
	_id = other.getID();
	rentedmovie = NULL; 
}

User::~User()
{
	delete rentedmovie;
}

string User::getID () const
{
	return _id;
}

string User::getName () const
{
	return _name;
}

Queue<Movie*> * User::movieQueue()
{
	Queue<Movie*> *temp = &usermoviebank;
	return temp;
}

void User::rentMovie(Movie *m)
{
	rentedmovie = m;
}

void User::returnMovie()
{
	rentedmovie = NULL;
}

Movie* User::currentMovie()
{
	return rentedmovie; //returns NULL if no movie checked out because movie is originally NULL and/or returnMovie sets it to NULL
}
