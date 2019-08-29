

#ifndef _SHACTIONHANDLER_H
#define _SHACTIONHANDLER_H

#include "Interface\ShCADWidget.h"
#include "Base\ShVariable.h"
#include <qcursor.h>
#include "Private\ShActionData.h"
#include "Data\ShAvailableDraft.h"
#include "Manager\ShLanguageManager.h"
#include "Manager\ShCommandLogManager.h"
#include "Private\ShActionTriggerFailureReason.h"

//State Pattern.

class QMouseEvent;
class QKeyEvent;
class QPainter;
class ShActionData;
class ShKeyHandler;
class ShAvailableCommands;

class ShActionHandler {

	friend class ShCommand;


protected:
	ShCADWidget *widget;
	ShKeyHandler *keyHandler;
	ShAvailableCommands *availableCommands;

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

	virtual ShPoint3d getLastBasePoint();

public:
	//*when enter key pressed, interpret current command text then do specific action.
	void interpret(const QString &command);

protected:
	virtual void triggerSucceeded();
	virtual void triggerFailed(ShActionTriggerFailureReason reason);
	virtual void trigger(const ShPoint3d &point);
	virtual void actionCanceled();
	virtual void actionFinished();

};

#endif //_SHACTIONHANDLER_H