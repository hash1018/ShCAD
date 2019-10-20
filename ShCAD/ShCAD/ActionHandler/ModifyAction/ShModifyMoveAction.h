
#ifndef _SHMODIFYMOVEACTION_H
#define _SHMODIFYMOVEACTION_H

#include "ShModifyAction.h"

class ShModifyMoveAction : public ShModifyAction {

public:
	enum Status {
		SelectingEntities,
		PickingBasePoint,
		PickingSecondPoint,

	};

private:
	Status status;
	ShPoint3d base;
	ShPoint3d previous;

public:
	ShModifyMoveAction(ShCADWidget *widget);
	~ShModifyMoveAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseRightPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual QCursor getCursorShape();
	virtual ShAvailableDraft getAvailableDraft();
	

	virtual void invalidate(ShPoint3d &point);

	virtual void finishSelectingEntities();

protected:
	virtual void trigger(const ShPoint3d &point);

};

#endif //_SHMODIFYMOVEACTION_H