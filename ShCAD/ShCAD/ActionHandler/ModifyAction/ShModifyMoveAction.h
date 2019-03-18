
#ifndef _SHMOVEACTION_H
#define _SHMOVEACTION_H

#include "ShModifyAction.h"
class ShModifyMoveAction : public ShModifyAction {

public:
	enum Status {
		SelectingEntities,
		FinishedSelectingEntities,
		PickedBasePoint,
	};

private:
	Status status;
	ShPoint3d base;
	ShPoint3d previous;

public:
	ShModifyMoveAction(ShGraphicView *graphicView);
	~ShModifyMoveAction();

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

#endif //_SHMOVEACTION_H