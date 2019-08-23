

#ifndef _SHACTIONHANDLER_H
#define _SHACTIONHANDLER_H

#include "Interface\ShCADWidget.h"
#include "Base\ShVariable.h"
#include <qcursor.h>
#include "Private\ShActionData.h"
#include "Data\ShAvailableDraft.h"

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

	virtual void keyPressEvent(ShActionData &data);

	virtual void draw(QPainter *painter);

	virtual ActionType getType() = 0;
	//*template method pattern.
	virtual ActionType getTypeIgnoringTemp();

	virtual QCursor getCursorShape();
	virtual QString getHeadTitle() = 0;

	//*template method pattern.
	void updateCommandEditHeadTitle();

	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);

	//*this called when temporaryAction Finished.
	virtual void temporaryActionFinished();

protected:
	virtual void triggerSucceeded();
	virtual void triggerFailed();
	virtual void trigger(const ShPoint3d &point);
	virtual void actionCanceled();
	virtual void actionFinished();

};

#endif //_SHACTIONHANDLER_H