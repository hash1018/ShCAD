#include "Interface\shcad.h"
#include <QtWidgets/QApplication>
#include <vld.h>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ShCAD w;

	//w.resize(1500, 800);


	w.showMaximized();
	return a.exec();
}
