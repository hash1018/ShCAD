


#ifndef _SHPANMOVEACTION_H
#define _SHPANMOVEACTION_H

#include "ShTemporaryAction.h"

class ShPanMoveAction : public ShTemporaryAction {

private:
	double prevX;
	double prevY;

public:
	ShPanMoveAction(ShGraphicView *graphicView, ShActionHandler *previousAction);
	~ShPanMoveAction();

	virtual void MousePressEvent(QMouseEvent *event);
	virtual void MouseMoveEvent(QMouseEvent *event);
	virtual void KeyPressEvent(QKeyEvent *event);
	virtual void MouseReleaseEvent(QMouseEvent *event);

	virtual ActionType GetType();

	virtual QCursor GetCursorShape();


};

#endif //_SHPANMOVEACTION_H