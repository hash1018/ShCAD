

#ifndef _SHSTATUSBAR_H
#define _SHSTATUSBAR_H

#include <qstatusbar.h>
#include "Data\ShPoint.h"

class QLabel;
class QAction;
class ShStateButton;
class ShNotifyEvent;

class ShStatusBar : public QStatusBar {
	Q_OBJECT

private:
	ShPoint3d point;
	double zoomRate;

	QLabel *coordiLabel;
	ShStateButton *orthogonalButton;
	ShStateButton *objectSnapButton;

public:
	ShStatusBar(QWidget *parent = nullptr);
	~ShStatusBar();

	void update(ShNotifyEvent *event);

private:
	void updateCoordiLabel();

};

#endif //_SHSTATUSBAR_H