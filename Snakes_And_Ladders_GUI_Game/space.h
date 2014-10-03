#ifndef SPACE_H
#define SPACE_H

#include <QMainWindow>
#include <QLabel>
#include <QPropertyAnimation>
#include <QPushButton>
#include "card.h"
#include "bank.h"
#include "player.h"

class Space
{

	public:
		Space();
		void checkspace(int position, Player &player, Player &player_next, Player &player_next2, Player &player_next3, int &event_index, int dicenumber_change, QLabel *labelPlayerIcon, QLabel *labelText, QPropertyAnimation *animate, QLabel *labelEvent, QPushButton *buttonYes, QPushButton *buttonNo, QPushButton *buttonDice, QLabel *labelShop, QLabel *labelDice, char &card_value, int &turn_num);
		char spacetype(int position);
		void outputbank();
		Bank _bank;

	private:
		int _value;
		int randomint;
		char _spacetype;
		int _tileposition[5][10];
		int _add;
		Card _deck;

	private slots:
		void Shop_Yes();
		void Shop_No();
};

#endif
