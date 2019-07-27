

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

	void setPoint(const ShPoint3d &point) { this->point = point; }
	void setZoomRate(const double &zoomRate) { this->zoomRate = zoomRate; }

	void updateCoordiLabel();

	void setOrthogonalButtonState(bool on);
	void setObjectSnapButtonState(bool on);

	private slots:
	void orthogonalButtonClicked();
	void objectSnapButtonClicked();
};

#endif //_SHSTATUSBAR_H