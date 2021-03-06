#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

#include "card.h"

using namespace std;

Card::Card()
{
	//Set up the Store Deck
	for(int counter=0;counter<15;counter++) //15 Double Toss cards
	{
		_deck[0][counter]='D';
	}
	for(int counter=15;counter<25;counter++) //10 Pushback cards
	{
		_deck[0][counter]='P';
	}
	for(int counter=25;counter<31;counter++) //6 Money Steal cards
	{
		_deck[0][counter]='M';
	}
	for(int counter=31;counter<40;counter++) //9 Swap cards
	{
		_deck[0][counter]='S';
	}
	//Set up the Event Deck
	for(int counter=0;counter<9;counter++) //+1 Dice Roll
	{
		_deck[1][counter]='+';
	}
	for(int counter=9;counter<18;counter++) //-1 Dice Roll
	{
		_deck[1][counter]='-';
	}
	for(int counter=18;counter<27;counter++) //No Pitfalls
	{
		_deck[1][counter]='P';
	}
	for(int counter=27;counter<36;counter++) //No Ladders
	{
		_deck[1][counter]='L';
	}
	for(int counter=36;counter<40;counter++) //Player Swap Cards
	{
		_deck[1][counter]='S';
	}

	_topcard0=0;
	_topcard1=0;
}

//Shuffle both decks
void Card::shuffle()
{
	srand(time(0));
	random_shuffle(_deck[0],_deck[0]+40);
	random_shuffle(_deck[1],_deck[1]+40);
}

char Card::draw(int type)
{
	char drawncard;
	if(type==0)
	{
		drawncard = _deck[0][_topcard0];
		_topcard0= ((_topcard0+1)%40);
		if(_topcard0==0) //If deck is used up, shuffle it
		{
			srand(time(0));
			random_shuffle(_deck[0],_deck[0]+40);
		}
	}
	else
	{
		drawncard = _deck[1][_topcard1];
		_topcard1= ((_topcard1+1)%40);
		if(_topcard1==0) //If deck is used up, shuffle it
		{
			srand(time(0));
			random_shuffle(_deck[1],_deck[1]+40);
		}
	}
	return drawncard;
}

void Card::output(int type)
{
	if(type==0)
	{
		cout << _deck[type][_topcard0]; //Outputs current card
		for(int i=0;i<40;i++)
		{
			cout << i << ": " << _deck[0][i] << endl;
		}
	}
	else
	{
		cout << _deck[type][_topcard1]; //Outputs current card		
		for(int i=0;i<40;i++)
		{
			cout << i << ": " << _deck[1][i] << endl;
		}
	}
}

