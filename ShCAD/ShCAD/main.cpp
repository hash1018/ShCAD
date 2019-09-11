
#include "Interface\ShCAD.h"
#include <QtWidgets/QApplication>
//#include <vld.h>
#include "Interface\Dialog\ShStartupDialog.h"
#include <qsplashscreen.h>

int main(int argc, char *argv[]) {

	QApplication a(argc, argv);

	ShStartupDialog dialog;

	if (dialog.exec() != QDialog::Accepted) {
		
		a.quit();
	}
	else {

		QSplashScreen splash;
		splash.show();
		
		ShCAD shCAD;
		shCAD.show();

		splash.finish(&shCAD);
		
		a.exec();
	}
	
	return 0;
}
