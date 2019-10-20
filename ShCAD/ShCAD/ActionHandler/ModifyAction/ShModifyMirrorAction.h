
#ifndef _SHMODIFYMIRRORACTION_H
#define _SHMODIFYMIRRORACTION_H

#include "ShModifyAction.h"

class ShModifyMirrorAction : public ShModifyAction {

public:
	enum Status {
		SelectingEntities,
		PickingBasePoint,
		PickingSecondPoint,

	};

private:
	Status status;
	ShPoint3d base;

public:
	ShModifyMirrorAction(ShCADWidget *widget);
	~ShModifyMirrorAction();

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

#endif //_SHMODIFYMIRRORACTION_H