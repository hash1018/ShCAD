#include "Interface\ShCAD.h"
#include <QtWidgets/QApplication>
//#include <vld.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ShCAD w;
	w.showMaximized();
	
	return a.exec();
}
