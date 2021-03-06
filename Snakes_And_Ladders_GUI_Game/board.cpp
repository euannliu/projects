#include <iostream>
#include <QMainWindow>
#include <QLabel>
using namespace std;

#include "board.h"
#include "space.h"
#include "player.h"

Board::Board()
{
}

void Board::Draw_Player_Position(Player player[4], QLabel *labelPlayerIcon[4], int num_players)
{
	for(int u=0;u<num_players;u++)
	{
		if(u==1|u==3)
		{
			p_x=24;
		}
		else
		{
			p_x=0;
		}
		if(u==2||u==3)
		{
			p_y=24;
		}
		else
		{
			p_y=0;
		}

		if(player[u].currentposition()>=0&&player[u].currentposition()<=4)
		{
			labelPlayerIcon[u]->move(284+(48*player[u].currentposition())+p_x,448+p_y);
		}
		else if(player[u].currentposition()>=5&&player[u].currentposition()<=9)
		{
			labelPlayerIcon[u]->move(476-(48*(player[u].currentposition()-5))+p_x,400+p_y);
		}
		else if(player[u].currentposition()>=10&&player[u].currentposition()<=14)
		{
			labelPlayerIcon[u]->move(284+(48*(player[u].currentposition()-10))+p_x,352+p_y);
		}
		else if(player[u].currentposition()>=15&&player[u].currentposition()<=19)
		{
			labelPlayerIcon[u]->move(476-(48*(player[u].currentposition()-15))+p_x,304+p_y);
		}
		else if(player[u].currentposition()>=20&&player[u].currentposition()<=24)
		{
			labelPlayerIcon[u]->move(284+(48*(player[u].currentposition()-20))+p_x,256+p_y);
		}
		else if(player[u].currentposition()>=25&&player[u].currentposition()<=29)
		{
			labelPlayerIcon[u]->move(476-(48*(player[u].currentposition()-25))+p_x,208+p_y);
		}
		else if(player[u].currentposition()>=30&&player[u].currentposition()<=34)
		{
			labelPlayerIcon[u]->move(284+(48*(player[u].currentposition()-30))+p_x,160+p_y);
		}
		else if(player[u].currentposition()>=35&&player[u].currentposition()<=39)
		{
			labelPlayerIcon[u]->move(476-(48*(player[u].currentposition()-35))+p_x,112+p_y);
		}
		

	}
}

void Board::Update_Status(QLabel *labelPlayerNumber[4], QLabel *labelPlayerName[4], QLabel *labelPlayerCharacter[4], QLabel *labelPlayerPosition[4], QLabel *labelPositionDisplay[4], QLabel *labelPlayerCurrency[4], QLabel *labelCurrencyDisplay[4], int num_players, Player player[4], QString stringName[4], bool player_active[4])
{
	int x_change, y_change;
	for(int l=0;l<num_players;l++)
	{
		if(l==0)
		{
			labelPlayerNumber[l] -> setText("Player 1");
			x_change=0;
			y_change=0;
		}
		else if(l==1)
		{
			labelPlayerNumber[l] -> setText("Player 2");
			x_change=528;
			y_change=0;
		}
		else if(l==2)
		{
			labelPlayerNumber[l] -> setText("Player 3");
			x_change=0;
			y_change=368;
		}
		else if(l==3)
		{
			labelPlayerNumber[l] -> setText("Player 4");
			x_change=528;
			y_change=368;
		}
		labelPlayerNumber[l] -> move(52+x_change,48+y_change);
		labelPlayerNumber[l] -> show();
	
		labelPlayerName[l] -> setText(stringName[l]);
		labelPlayerName[l] -> move(72+x_change,72+y_change);
		labelPlayerName[l] -> show();
		
		labelPlayerCharacter[l] -> move(52+x_change,78+y_change);
	
		labelPositionDisplay[l] -> setText("Position:");
		labelPositionDisplay[l] -> move(52+x_change,96+y_change);
		labelPositionDisplay[l] -> show();
	
		labelPlayerPosition[l] -> setNum(player[l].currentposition()+1);
		labelPlayerPosition[l] -> move(128+x_change,96+y_change);
		labelPlayerPosition[l] -> show();	
	
		labelCurrencyDisplay[l] -> setText("Currency:");
		labelCurrencyDisplay[l] -> move(52+x_change,114+y_change);
		labelCurrencyDisplay[l] -> show();
	
		labelPlayerCurrency[l] -> setNum(player[l].currentcurrency());
		labelPlayerCurrency[l] -> move(128+x_change,114+y_change);
		labelPlayerCurrency[l] -> show();

		if(!player_active[l])
		{
			labelPositionDisplay[l] -> hide();
			labelPlayerPosition[l] -> hide();	
			labelCurrencyDisplay[l] -> hide();
			labelPlayerCurrency[l] -> hide();
		}
	}
}
