

#ifndef _SHMODIFYCOPYACTION_H
#define _SHMODIFYCOPYACTION_H

#include "ShModifyAction.h"

class ShAddEntityTransaction;
class ShModifyCopyAction : public ShModifyAction {

public:
	enum Status {
		SelectingEntities,
		PickingBasePoint,
		PickingSecondPoint,

	};

private:
	ShAddEntityTransaction *transaction;
	Status status;
	ShPoint3d base;
	ShPoint3d previous;

public:
	ShModifyCopyAction(ShCADWidget *widget);
	~ShModifyCopyAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseRightPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual QCursor getCursorShape();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);

	virtual void finishSelectingEntities();

private:
	void addCopiedEntities(const QLinkedList<ShEntity*> &list);

protected:
	virtual void trigger(const ShPoint3d &point);
};

#endif //_SHMODIFYCOPYACTION_H