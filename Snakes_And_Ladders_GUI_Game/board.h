#ifndef BOARD_H
#define BOARD_H

#include "space.h"
#include "player.h"
#include <QMainWindow>
#include <QLabel>


class Board
{
	private:
		Space space;
		int p_y;
		int p_x;
	public:
		Board();
		void Draw_Player_Position(Player player[4], QLabel *labelPlayerIcon[4], int num_players);
		void Update_Status(QLabel *labelPlayerNumber[4], QLabel *labelPlayerName[4], QLabel *labelPlayerCharacter[4], QLabel *labelPlayerPosition[4], QLabel *labelPositionDisplay[4], QLabel *labelPlayerCurrency[4], QLabel *labelCurrencyDisplay[4], int num_players, Player player[4], QString stringName[4], bool player_active[4]);
};

#endif
