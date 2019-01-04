


#ifndef _SHCADWIDGET_H
#define _SHCADWIDGET_H

#include <qwidget.h>

class ShGraphicView;
class ShCADWidget : public QWidget {
	
private:
	ShGraphicView *graphicView;

public:
	ShCADWidget(ShGraphicView *graphicView, QWidget *parent = 0);
	~ShCADWidget();

protected:
	void resizeEvent(QResizeEvent *event);
	
};

#endif //_SHCADWIDGET_H