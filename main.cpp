#include "chooseInsulator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	chooseInsulator w;
	w.show();
	return a.exec();
}
