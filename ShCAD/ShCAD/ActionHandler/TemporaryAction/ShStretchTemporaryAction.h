

#ifndef _SHSELECTIONMOVEACTION_H
#define _SHSELECTIONMOVEACTION_H

#include "ActionHandler\TemporaryAction\ShTemporaryAction.h"
#include <qlinkedlist.h>
#include "ShPoint.h"

class ShEntity;
class ShStretchTemporaryAction : public ShTemporaryAction {

private:
	ShPoint3d vertex;
	QLinkedList<ShEntity*> list;
	QLinkedList<HitPoint> hitList;

public:
	ShStretchTemporaryAction(ShGraphicView *graphicView,
		const QLinkedList<ShEntity*>& list, const QLinkedList<HitPoint>& hitList, ShPoint3d vertex);
	ShStretchTemporaryAction(ShGraphicView *graphicView, ShActionHandler *previousAction,
		const QLinkedList<ShEntity*>& list, const QLinkedList<HitPoint>& hitList, ShPoint3d vertex);
	~ShStretchTemporaryAction();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	

	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data);

	virtual void Draw(QPainter *painter);
	virtual QCursor GetCursorShape();
	virtual ActionType GetType();

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);

private:
	void DrawVertex();
	void EraseVertex();
};

#endif //_SHSELECTIONMOVEACTION_H