

#ifndef _SHACTIONHANDLER_H
#define _SHACTIONHANDLER_H

#include "Interface\ShCADWidget.h"
#include "Base\ShVariable.h"
#include <qcursor.h>
#include "Private\ShActionData.h"

//State Pattern.

class QMouseEvent;
class QKeyEvent;
class QPainter;
class ShActionData;
class ShKeyHandler;

class ShActionHandler {

protected:
	ShCADWidget *widget;
	ShKeyHandler *keyHandler;

public:
	ShActionHandler(ShCADWidget *widget);
	virtual ~ShActionHandler() = 0;

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMidPressEvent(ShActionData &data);
	virtual void mouseRightPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);
	virtual void mouseReleaseEvent(ShActionData &data);

	void keyPressEvent(ShActionData &data);

	virtual void draw(QPainter *painter);

	virtual ActionType getType() = 0;
	virtual QCursor getCursorShape();
	virtual QString getHeadTitle() = 0;

	//*template method pattern.
	void updateCommandEditHeadTitle();

};

#endif //_SHACTIONHANDLER_H