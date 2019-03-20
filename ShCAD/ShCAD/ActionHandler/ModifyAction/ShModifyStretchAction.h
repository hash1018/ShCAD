
#ifndef _SHMODIFYSTRETCHACTION_H
#define _SHMODIFYSTRETCHACTION_H

#include "ShModifyAction.h"
class ShModifyStretchAction : public ShModifyAction {

public:
	enum Status {
		SelectingEntities,
		FinishedSelectingEntities,
		PickedBasePoint,
	};

private:
	Status status;
	ShPoint3d base;
	QLinkedList<ShEntity*> list;
	QLinkedList<VertexPoint> vertexList;

public:
	ShModifyStretchAction(ShGraphicView *graphicView);
	~ShModifyStretchAction();

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

protected:
	virtual void DoFollowUpWithFoundEntity(ShEntity* foundEntity, Qt::KeyboardModifiers modifier);
};
#endif //_SHMODIFYSTRETCHACTION_H