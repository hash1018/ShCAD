

#ifndef _SHSTATUSBAR_H
#define _SHSTATUSBAR_H

#include <qstatusbar.h>


class QLabel;
class QAction;
class ShStateButton;

class ShStatusBar : public QStatusBar {
	Q_OBJECT

private:
	QLabel *coordinates;
	ShStateButton *orthogonalButton;
	ShStateButton *objectSnapButton;

public:
	ShStatusBar(QWidget *parent = nullptr);
	~ShStatusBar();

	//void update(NotifyEvent *event);

};

#endif //_SHSTATUSBAR_H