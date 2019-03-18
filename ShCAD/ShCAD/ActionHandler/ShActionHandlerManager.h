

#ifndef _SHACTIONHANDLERMANAGER_H
#define _SHACTIONHANDLERMANAGER_H

#include "ShVariable.h"
#include <qcursor.h>
#include "ShDraft.h"

class ShTemporaryAction;
class ShGraphicView;
class ShActionHandler;
class QMouseEvent;
class QKeyEvent;
class QPainter;
class ShActionHandlerDecorator;
class ShActionHandlerManager{

private:
	ShActionHandler *currentAction;
	ShActionHandlerDecorator *actionDecorator;
	ShGraphicView *graphicView;
	ShDraftFlag draftFlag;
	ObjectSnap disposableSnap;

public:
	ShActionHandlerManager(ShGraphicView *graphicView, const ShDraftFlag& draftFlag);
	~ShActionHandlerManager();

	virtual void LMousePressEvent(QMouseEvent *event);
	virtual void MMousePressEvent(QMouseEvent *event);
	virtual void RMousePressEvent(QMouseEvent *event);

	virtual void MouseMoveEvent(QMouseEvent *event);
	virtual void MouseReleaseEvent(QMouseEvent *event);
	virtual void KeyPressEvent(QKeyEvent *event);

	void ChangeAction(ActionType actionType);

	//Unlike method ChangeAction, this do not delete currentAction. Just replace it.
	void ReplaceAction(ShActionHandler *actionHandler);
	
	void SetTemporaryAction(ShTemporaryAction *temporaryAction);
	QCursor GetCursorShape();
	ActionType GetType();

	void Draw(QPainter *painter);
	void SetDraftFlag(const ShDraftFlag& draftFlag);
	void SetDisposableObjectSnap(ObjectSnap objectSnap);

	bool EnabledDrawEntityVertex();

	inline const ShActionHandler* GetCurrentAction() const { return this->currentAction; }


private:
	void ChangeActionDecorator();
};

#endif //_SHACTIONHANDLERMANAGER_H