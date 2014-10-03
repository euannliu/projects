
#include <QApplication>
#include "game.h"

int main(int argv, char* argc[])
{

	QApplication app(argv, argc);
	Game game;
	game.show();

	return app.exec();

}
