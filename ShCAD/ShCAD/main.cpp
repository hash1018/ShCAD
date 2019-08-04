#include "Interface\ShCAD.h"
#include <QtWidgets/QApplication>
//#include <vld.h>
#include "Manager\ShLanguageManager.h"
#include "Interface\Dialog\ShStartupDialog.h"

int main(int argc, char *argv[]) {

	QApplication a(argc, argv);

	ShLanguageManager::getInstance()->setLanguage(ShLanguageManager::Korean);
	

	ShStartupDialog dialog;

	if (dialog.exec() != QDialog::Accepted) {
		
		a.quit();
	}
	else {
		ShCAD shCAD;
		shCAD.showMaximized();
		a.exec();
	}
	
	return 0;
}
