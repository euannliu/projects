#include <QApplication>
#include "Notflix.h"

int main(int argc, char* argv[])
{

	QApplication app(argc, argv);
	Notflix program(argc, argv);
	program.show();

	return app.exec();

}
