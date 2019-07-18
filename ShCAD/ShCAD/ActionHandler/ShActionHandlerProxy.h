

#ifndef _SHACTIONHANDLERPROXY_H
#define _SHACTIONHANDLERPROXY_H

#include "Base\ShVariable.h"
#include <qcursor.h>

class QMouseEvent;
class QKeyEvent;
class ShActionHandler;
class ShCADWidget;
class ShTemporaryAction;
class QPainter;

class ShActionHandlerProxy {

private:
	ShCADWidget *widget;
	ShActionHandler *currentAction;

public:
	ShActionHandlerProxy(ShCADWidget *widget);
	~ShActionHandlerProxy();

	void mouseLeftPressEvent(QMouseEvent *event);
	void mouseMidPressEvent(QMouseEvent *event);
	void mouseRightPressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);

	void setCurrentAction(ShActionHandler *actionHandler);

	QCursor getCursorShape();
	ActionType getType();

	void draw(QPainter *painter);

	inline ShActionHandler* getCurrentAction() const { return this->currentAction; }

};



#endif //_SHACTIONHANDLERPROXY_H