


#ifndef _SHGRAPHICVIEW_H
#define _SHGRAPHICVIEW_H

#include <qopenglwidget.h>

class ShCADWidget;
class ShGraphicView : public QOpenGLWidget {

	friend class ShCADWidget;

public:
	ShGraphicView(QWidget *parent = 0);
	virtual ~ShGraphicView() = 0;

};

#endif //_SHGRAPHICVIEW_H