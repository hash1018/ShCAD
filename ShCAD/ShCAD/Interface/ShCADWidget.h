

#ifndef _SHCADWidget_H
#define _SHCADWidget_H

#include <qopenglwidget.h>

class ShNotifyEvent;

class ShCADWidget : public QOpenGLWidget {

public:
	ShCADWidget(QWidget *parent = nullptr);
	~ShCADWidget();

	void notify(ShNotifyEvent *event);

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


};

#endif //_SHCADWIDGET_H