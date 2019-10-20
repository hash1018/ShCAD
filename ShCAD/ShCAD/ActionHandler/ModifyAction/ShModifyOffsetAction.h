
#ifndef _SHMODIFYOFFSETACTION_H
#define _SHMODIFYOFFSETACTION_H

#include "ShModifyAction.h"
#include "Command\ShCustomCommand.h"

class ShEntity;
class ShAddEntityTransaction;

class ShModifyOffsetAction : public ShModifyAction {

public:
	enum Status {
		InputtingNumber,
		PickingSecondPoint,
		SelectingEntityToModify,
		PickingPointOnSideToOffset,
	};

private:
	ShAddEntityTransaction *transaction;
	ShOnlyNumberCommand<ShModifyOffsetAction> *command;
	Status status;
	double offsetDistance;
	ShPoint3d firstPickPoint;
	ShEntity *entityToOffset;

public:
	ShModifyOffsetAction(ShCADWidget *widget);
	~ShModifyOffsetAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual QCursor getCursorShape();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void finishSelectingEntities();

	virtual void invalidate(ShPoint3d &point);

protected:
	virtual void trigger(const ShPoint3d &point);

private:
	void inputNumber(void *number);
	void addEntity(ShEntity *entity);
};

#endif //_SHMODIFYOFFSETACTION_H