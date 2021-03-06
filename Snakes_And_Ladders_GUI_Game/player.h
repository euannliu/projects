#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <cstring>

using namespace std;

class Player
{
	private:
		int _position;
		int _currency;
		int _job;
		string _name;
		bool _win;
	public:
		Player();
		void label(string name, int job);
		void addposition(int position);
		void setposition(int position);
		int currentposition();
		void addcurrency(int currency);
		void subcurrency(int currency);
		int currentcurrency();
		void outputjob();
		int outputjobindex();
		void outputname();
		bool checkvictory();
		string returnname();
};

#endif
