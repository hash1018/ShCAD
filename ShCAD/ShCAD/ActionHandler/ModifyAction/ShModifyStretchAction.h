

#ifndef _SHMODIFYSTRETCHACTION_H
#define _SHMODIFYSTRETCHACTION_H

#include "ShModifyAction.h"

class ShEntity;
class ShStretchData;

class ShModifyStretchAction : public ShModifyAction {

public:
	enum Status {
		SelectingEntities,
		PickingBasePoint,
		PickingSecondPoint,

	};

private:
	QLinkedList<ShEntity*> possibleStretchEntities;
	QLinkedList<ShStretchData*> stretchDatas;
	Status status;
	ShPoint3d base;

public:
	ShModifyStretchAction(ShCADWidget *widget);
	~ShModifyStretchAction();

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

private:
	virtual void triggerSelectingEntities(QMouseEvent *event);
	virtual void selectFoundEntity(ShEntity *foundEntity, Qt::KeyboardModifiers modifier);
};

#endif //_SHMODIFYSTRETCHACTION_H