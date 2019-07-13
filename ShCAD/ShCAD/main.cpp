#include "Interface\ShCAD.h"
#include <QtWidgets/QApplication>
#include <vld.h>
#include "Manager\ShLanguageManager.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	ShLanguageManager::getInstance()->setLanguage(ShLanguageManager::Korean);

	ShCAD w;
	w.showMaximized();
	
	return a.exec();
}
