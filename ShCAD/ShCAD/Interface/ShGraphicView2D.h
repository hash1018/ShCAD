

#ifndef _SHGRAPHICVIEW2D_H
#define _SHGRAPHICVIEW2D_H

#include "ShGraphicView.h"

class ShGraphicView2D : public ShGraphicView {

public:
	ShGraphicView2D(QWidget *parent = 0);
	~ShGraphicView2D();


protected:

	virtual void initializeGL();
	virtual void paintGL();

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);

};

#endif //_SHGRAPHICVIEW2D_H