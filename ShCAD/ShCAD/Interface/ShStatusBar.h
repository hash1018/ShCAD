

#ifndef _SHSTATUSBAR_H
#define _SHSTATUSBAR_H

#include <qstatusbar.h>
class QLabel;
class QAction;
class ShStatusBar : public QStatusBar {

private:
	QLabel *coordinates;

public:
	ShStatusBar(QWidget *parent = 0);
	~ShStatusBar();

	void Update(double x, double y, double z, double zoomRate);

};

#endif //_SHSTATUSBAR_H