

#ifndef _SHDRAGSELECTACTION_H
#define _SHDRAGSELECTACTION_H

#include "ShTemporaryAction.h"
class ShDragSelectAction : public ShTemporaryAction {

private:
	double firstX;
	double firstY;
	double secondX;
	double secondY;

public:
	ShDragSelectAction(ShGraphicView *graphicView, ShActionHandler *previousAction, double firstX,double firstY);
	~ShDragSelectAction();

	virtual void MousePressEvent(QMouseEvent *event);
	virtual void MouseMoveEvent(QMouseEvent *event);
	virtual void KeyPressEvent(QKeyEvent *event);
	

	virtual ActionType GetType();

	virtual QCursor GetCursorShape();
	virtual void Draw(QPainter *painter);
};

#endif //_SHDRAGSELECTACTION_H