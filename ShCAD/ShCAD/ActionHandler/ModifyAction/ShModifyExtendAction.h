
#ifndef _SHMODIFYEXTENDACTION_H
#define _SHMODIFYEXTENDACTION_H

#include "ShModifyAction.h"
class ShModifyExtendAction : public ShModifyAction {

public:
	enum Status {
		SelectingEntities,
		FinishedSelectingEntities,
	};

private:
	Status status;

public:
	ShModifyExtendAction(ShGraphicView *graphicView);
	~ShModifyExtendAction();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void RMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data);
	virtual ActionType GetType();

	virtual QCursor GetCursorShape();
	virtual QString GetActionHeadTitle();

private:
	void UpdateNextListText();
};

#endif //_SHMODIFYMOVEACTION_H