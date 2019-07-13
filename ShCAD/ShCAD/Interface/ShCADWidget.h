

#ifndef _SHCADWidget_H
#define _SHCADWidget_H

#include <qopenglwidget.h>
#include "Data\ShPoint.h"
#include "Interface\Private\ShAxis.h"
#include "Base\ShVariable.h"
#include "Data\ShScrollPosition.h"

class ShNotifyEvent;

class ShCADWidget : public QOpenGLWidget {

private:
	ShPoint3d coordinate;
	double zoomRate;
	ShAxis axis;
	ShScrollPosition scroll;
	DrawType drawType;
	QImage capturedImage;
	

public:
	ShCADWidget(QWidget *parent = nullptr);
	~ShCADWidget();

	void notify(ShNotifyEvent *event);
	void update(ShNotifyEvent *event);
	void update(DrawType drawType = DrawType::DrawAll);

	void convertDeviceToEntity(const int &x, const int &y, double &ex, double &ey);
	void convertEntityToDevice(const double &x, const double &y, int &dx, int &dy);

	void captureImage();

protected:
	virtual void initializeGL();
	virtual void paintGL();
	virtual void resizeGL(int width, int height);

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void wheelEvent(QWheelEvent *event);
	virtual void focusInEvent(QFocusEvent *event);


public:
	void setCoordinate(const ShPoint3d &coordinate) { this->coordinate = coordinate; }
	void setScrollPosition(const ShScrollPosition &scrollPosition) { this->scroll = scrollPosition; }
	void setZoomRate(const double &zoomRate) { this->zoomRate = zoomRate; }

public:
	inline ShPoint3d getCoordinate() const { return this->coordinate; }
	inline ShScrollPosition getScrollPosition() const { return this->scroll; }
	inline double getZoomRate() const { return this->zoomRate; }
	inline ShAxis& getAxis() const { return const_cast<ShAxis&>(this->axis); }
	inline DrawType getDrawType() const { return this->drawType; }
	inline const QImage& getCapturedImage() const { return const_cast<QImage&>(this->capturedImage); }
};

#endif //_SHCADWIDGET_H