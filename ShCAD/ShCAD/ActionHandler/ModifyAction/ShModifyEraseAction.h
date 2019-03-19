
#ifndef _SHMODIFYERASEACTION_H
#define _SHMODIFYERASEACTION_H

#include "ShModifyAction.h"
class ShModifyEraseAction : public ShModifyAction {

public:
	enum Status {
		SelectingEntities,
	};

private:
	Status status;
	


public:
	ShModifyEraseAction(ShGraphicView *graphicView);
	~ShModifyEraseAction();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void RMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data);
	virtual ActionType GetType();

	virtual QCursor GetCursorShape();
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);
	virtual void ApplyOrthogonalShape(bool on);

private:
	void UpdateNextListText();
};
#endif //_SHMODIFYERASEACTION_H