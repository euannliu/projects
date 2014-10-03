#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <cstring>
#include <QMainWindow>
#include <QObject>
#include <QtGui>

using namespace std;

#include "space.h"
#include "card.h"
#include "bank.h"
#include "player.h"

Space::Space()
{
	//Making all the spaces empty first

/*	for(counter_a=0;counter_a<6;counter_a++)
	{
		for(counter_b=0;counter_b<10;counter_b++)
		{
			_tileposition[counter_a][counter_b] = -1;
		}
	}*/

	//Assigning special tiles to spaces

	for(int a=0;a<10;a++)
	{
		_tileposition[0][a] = -1;
		_tileposition[1][a] = -1;
		_tileposition[2][a] = -1;
		_tileposition[3][a] = -1;
	}

		//Pitfalls
		_tileposition[0][0] = 37;
		_tileposition[0][1] = 28;
		_tileposition[0][2] = 30;
		_tileposition[0][3] = 17;
		_tileposition[0][4] = 14;
		_tileposition[0][5] = 9;
		_tileposition[0][6] = 6;

		//Ladders
		_tileposition[1][0] = 33;
		_tileposition[1][1] = 23;
		_tileposition[1][2] = 11;
		_tileposition[1][3] = 2;

		//Shops
		_tileposition[2][0] = 13;
		_tileposition[2][1] = 19;
		_tileposition[2][2] = 25;
		_tileposition[2][3] = 35;

		//Events
		_tileposition[3][0] = 1;
		_tileposition[3][1] = 10;
		_tileposition[3][2] = 15;
		_tileposition[3][3] = 27;
		_tileposition[3][4] = 34;

		//Money
		_tileposition[4][0] = 4;
		_tileposition[4][1] = 20;
		_tileposition[4][2] = 8;
		_tileposition[4][3] = 16;
		_tileposition[4][4] = 22;
		_tileposition[4][5] = 24;
		_tileposition[4][6] = 29;
		_tileposition[4][7] = 31;
		_tileposition[4][8] = 38;

	_deck.shuffle();
}


void Space::checkspace(int position, Player &player, Player &player_next, Player &player_next2, Player &player_next3, int &event_index,int dicenumber_change, QLabel *labelPlayerIcon,QLabel *labelText, QPropertyAnimation *animate, QLabel *labelEvent, QPushButton *buttonYes, QPushButton *buttonNo, QPushButton *buttonDice, QLabel *labelShop, QLabel *labelDice, char &card_value, int &turn_num)
{
	animate -> setTargetObject(labelPlayerIcon);
	Player player_hold; //For Swap Event
	int position_hold; //for the Swap Event
	//int check; //for Shop event
	//int dicenumber; //For recursion
	//char input; //for Shop event
	//char dummy[8]; //For a Shop event 
	char card;
	labelText -> setText("Landed on a blank tile...");
	for(int counter=0;counter<10;counter++)
	{
		if(position==_tileposition[0][counter]&&event_index!=3) //Pitfall - Calculates player's position so they drop exactly one level lower
		{
			if(position%10==0||position%10==5)
			{
				_add=-1;
			}
			else if(position%10==1||position%10==6)
			{
				_add=-3;
			}
			else if(position%10==2||position%10==7)
			{
				_add=-5;
			}
			else if(position%10==3||position%10==8)
			{
				_add=-7;
			}
			else if(position%10==9||position%10==4)
			{
				_add=-9;
			}
			srand(time(NULL));
			randomint=rand()%5+1;
			
			if(randomint==1)
			{
				labelText -> setText("Landed on a Pitfall! Too unlucky!");
				//cout << "\nLANDED ON PITFALL\nTOO UNLUCKY!";
			}
			else if(randomint==2)
			{
				labelText -> setText("Landed on a Pitfall! See you next fall!");
				//cout << "\nLANDED ON PITFALL\nSEE YOU NEXT FALL!";
			}
			else if(randomint==3)
			{
				labelText -> setText("Landed on a Pitfall! Have a nice trip!");
				//cout << "\nLANDED ON PITFALL\nHAVE A NICE TRIP!";
			}
			else if(randomint==4)
			{
				labelText -> setText("Landed on a Pitfall! Karma!");
				//cout << "\nLANDED ON PITFALL\nKARMA!";
			}
			else
			{
				labelText -> setText("Landed on a Pitfall! Loser!");
				//cout << "\nLANDED ON PITFALL\nLOSER!";
			}

			/*animate->setDuration(10000);
			animate->setStartValue(QRect(0, 0, 100, 30));
			animate->setEndValue(QRect(250, 250, 100, 30));
			animate->start();*/

			player.setposition(position+_add);
			
		}

		if(position==_tileposition[1][counter]&&event_index!=4) //Ladder - Calculates player's position so they go up one level
		{
			if(position%10==9||position%10==4)
			{
				_add=1;
			}
			else if(position%10==3||position%10==8)
			{
				_add=3;
			}
			else if(position%10==2||position%10==7)
			{
				_add=5;
			}
			else if(position%10==1||position%10==6)
			{
				_add=7;
			}
			else if(position%10==0||position%10==5)
			{
				_add=9;
			}
			srand(time(NULL));
			randomint=rand()%4+1;
			
			if(randomint==1)
			{
				labelText -> setText("Landed on a Ladder! Ascend to Heaven!");
				//cout << "\nLANDED ON LADDER\nASCEND TO HEAVEN!";
			}
			else if(randomint==2)
			{
				labelText -> setText("Landed on a Ladder! Spring forward!");
				//cout << "\nLANDED ON LADDER\nSPRING FORWARD!";
			}
			else if(randomint==3)
			{
				labelText -> setText("Landed on a Ladder! Up, up you go!");
				//cout << "\nLANDED ON LADDER\nUP, UP YOU GO!";
			}
			else
			{
				labelText -> setText("Landed on a Ladder! Lift off!");
				//cout << "\nLANDED ON LADDER\nLIFT OFF!";
			}

			player.setposition(position+_add);

		}

		if(position==_tileposition[2][counter]) //Shop - Players can draw a shop card. This section checks if the player has enough money and then acts
		{
			labelText -> setText("Buy?");
			buttonDice -> move(0,400);
			buttonYes -> show();
			buttonNo -> show();
			card=_deck.draw(0);
			if(card=='D')
			{
				labelShop -> setPixmap(QPixmap("gfx/Shop_Double.png"));
				labelShop -> show();
				card_value = 'D';
			}
			else if(card=='P')
			{
				labelShop -> setPixmap(QPixmap("gfx/Shop_Pushback.png"));
				labelShop -> show();
				card_value = 'P';
			}
			else if(card=='M')
			{
				labelShop -> setPixmap(QPixmap("gfx/Shop_Money.png"));
				labelShop -> show();
				card_value = 'M';
			}
			else
			{
				labelShop -> setPixmap(QPixmap("gfx/Shop_Swap.png"));
				labelShop -> show();
				card_value = 'S';
			}
			turn_num--;
		}

		if(position==_tileposition[3][counter]) //Event
		{
			card=_deck.draw(1);
			if(card=='+')
			{
				labelText -> setText("Drew an Event Card! All movement +1");
				//cout << "\nDREW AN EVENT CARD!\nThe Dice++ Card increases all dice rolls by 1";
				event_index=1;	
				labelEvent -> setPixmap(QPixmap("gfx/Event_Dice_Plus.png"));
				labelEvent -> show();
			}
			else if(card=='-')
			{
				labelText -> setText("Drew an Event Card! All movement -1");
				//cout << "\nDREW AN EVENT CARD!\nThe Dice-- Card decreases all dice rolls by 1";
				event_index=2;
				labelEvent -> setPixmap(QPixmap("gfx/Event_Dice_Minus.png"));
				labelEvent -> show();
			}
			else if(card=='P')
			{
				labelText -> setText("Drew an Event Card! No Pitfalls!");
				//cout << "\nDREW AN EVENT CARD!\nThe Pitfall Card removes all pitfalls";
				event_index=3;
				labelEvent -> setPixmap(QPixmap("gfx/Event_Pitfall.png"));
				labelEvent -> show();
			}
			else if(card=='L')
			{
				labelText -> setText("Drew an Event Card! No Ladders...");
				//cout << "\nDREW AN EVENT CARD!\nThe Ladder Card removes all ladders";
				event_index=4;
				labelEvent -> setPixmap(QPixmap("gfx/Event_Ladders.png"));
				labelEvent -> show();
			}
			else if(card=='S')
			{
				labelText -> setText("Drew an Event Card! Players swapped");
				//cout << "\nDREW AN EVENT CARD!\nThe Swap Card swaps player positions";
				labelEvent -> setPixmap(QPixmap("gfx/Event_Swap.png"));
				labelEvent -> show();

				position_hold=player.currentposition();
				player.setposition(player_next.currentposition());
				player_next.setposition(position_hold);

				position_hold=player_next2.currentposition();
				player_next2.setposition(player_next3.currentposition());
				player_next3.setposition(position_hold);

				//cout << endl;
				//player_next.outputname();
				//cout << " is now on tile number: " << player_next.currentposition()+1 << endl;
				//player_next2.outputname();
				//cout << " is now on tile number: " << player_next2.currentposition()+1 << endl;
				//player_next3.outputname();
				//cout << " is now on tile number: " << player_next3.currentposition()+1;
			}
		}

		if(position==_tileposition[4][counter]) //Money
		{
			if(_bank.withdraw(0)>100)
			{
				labelText -> setText("You collected 200 coins!");
				//cout << "\nLANDED ON A MONEY SPACE. GAINED 200 COINS!";
				_bank.withdraw(200);
				player.addcurrency(200);
			}
			else
			{
				labelText -> setText("Not enough coins lying around...");
				//cout << "\nDOESN'T SEEM TO BE ENOUGH COINS LYING AROUND...";
			}
		}
	}
	//cout << endl;
	//player.outputname();
	//cout << " is now on tile number: " << player.currentposition()+1 << endl;
}

char Space::spacetype(int position)
{
	char output;
	for(int counter=0;counter<10;counter++)
	{
		if(position==39) //Finish Line
		{
			output='F';
			return output;	
		}
		if(position==_tileposition[0][counter]) //Pitfall
		{
			output='P';
			return output;			
		}

		if(position==_tileposition[1][counter]) //Ladder
		{
			output='L';
			return output;	
		}
		if(position==_tileposition[3][counter]) //Events
		{
			output='E';
			return output;	
		}
		if(position==_tileposition[4][counter]) //Money
		{
			output='*';
			return output;	
		}
		if(position==_tileposition[2][counter]) //Shop
		{
			output='$';
			return output;	
		}
	}
	output=' ';
	return output;	
}

void Space::outputbank()
{
	//cout << _bank.withdraw(0);
}


