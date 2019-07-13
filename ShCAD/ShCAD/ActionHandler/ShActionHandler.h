

#ifndef _SHACTIONHANDLER_H
#define _SHACTIONHANDLER_H

#include "Base\ShVariable.h"
#include <qcursor.h>

class ShCADWidget;
class QMouseEvent;
class QKeyEvent;
class QPainter;
class ShActionData;

class ShActionHandler {

protected:
	ShCADWidget *widget;

public:
	ShActionHandler(ShCADWidget *widget);
	virtual ~ShActionHandler() = 0;

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMidPressEvent(ShActionData &data);
	virtual void mouseRightPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);
	virtual void mouseReleaseEvent(ShActionData &data);

	virtual void keyPressEvent(ShActionData &data);

	virtual void draw(QPainter *painter);

	virtual ActionType getType() = 0;
	virtual QCursor getCursorShape();

};

#endif //_SHACTIONHANDLER_H