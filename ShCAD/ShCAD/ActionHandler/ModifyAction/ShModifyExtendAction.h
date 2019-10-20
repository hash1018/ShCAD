
#ifndef _SHMODIFYEXTENDACTION_H
#define _SHMODIFYEXTENDACTION_H

#include "ShModifyAction.h"

class ShExtendEntityTransaction;

class ShModifyExtendAction : public ShModifyAction {

public:
	enum Status {
		SelectingEntities,
		SelectingEntityToModify,

	};

private:
	ShExtendEntityTransaction *transaction;
	Status status;

public:
	ShModifyExtendAction(ShCADWidget *widget);
	~ShModifyExtendAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseRightPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual QCursor getCursorShape();


	virtual void invalidate(ShPoint3d &point);

	virtual void finishSelectingEntities();

protected:
	virtual void trigger(const ShPoint3d &point);

private:
	void extend(ShEntity *original, ShEntity *extendedEntity);

};

#endif //_SHMODIFYEXTENDACTION_H