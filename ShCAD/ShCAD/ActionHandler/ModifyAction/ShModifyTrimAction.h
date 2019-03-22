

#ifndef _SHMODIFYTRIMACTION_H
#define _SHMODIFYTRIMACTION_H

#include "ShModifyAction.h"
class ShModifyTrimAction : public ShModifyAction {

public:
	enum Status {
		SelectingEntities,
		FinishedSelectingEntities,
	};

private:
	Status status;

public:
	ShModifyTrimAction(ShGraphicView *graphicView);
	~ShModifyTrimAction();

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

#endif //_SHMODIFYTRIMACTION_H