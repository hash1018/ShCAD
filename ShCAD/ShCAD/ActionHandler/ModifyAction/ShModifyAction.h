
#ifndef _SHMODIFYACTION_H
#define _SHMODIFYACTION_H

#include "ActionHandler\ShActionHandler.h"

class ShModifyAction : public ShActionHandler {

public:
	enum Status {
		SelectingEntities,
		PickingBasePoint,
		PickingSecondPoint,
	};

protected:
	Status status;
	ShPoint3d base;
	ShPoint3d previous;

public:
	ShModifyAction(ShCADWidget *widget);
	virtual ~ShModifyAction() = 0;

	virtual QCursor getCursorShape();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void finishSelectingEntities() = 0;

protected:
	virtual void triggerSelectingEntities(QMouseEvent *event);

private:
	virtual void selectFoundEntity(ShEntity *foundEntity, Qt::KeyboardModifiers modifier);

};

#endif //_SHMODIFYACTION_H