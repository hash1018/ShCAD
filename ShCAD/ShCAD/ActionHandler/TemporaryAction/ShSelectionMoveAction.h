

#ifndef _SHSELECTIONMOVEACTION_H
#define _SHSELECTIONMOVEACTION_H

#include "ActionHandler\TemporaryAction\ShTemporaryAction.h"
#include <qlinkedlist.h>
#include "ShPoint.h"

class ShEntity;
class ShSelectionMoveAction : public ShTemporaryAction {

private:
	ShPoint3d vertex;
	QLinkedList<ShEntity*> list;
	QLinkedList<HitPoint> hitList;

public:
	ShSelectionMoveAction(ShGraphicView *graphicView, ShActionHandler *previousAction,
		const QLinkedList<ShEntity*>& list, const QLinkedList<HitPoint>& hitList, ShPoint3d vertex);
	~ShSelectionMoveAction();

	virtual void MousePressEvent(QMouseEvent *event);
	virtual void MouseMoveEvent(QMouseEvent *event);
	virtual void KeyPressEvent(QKeyEvent *event);

	virtual void Draw(QPainter *painter);
	virtual QCursor GetCursorShape();
	virtual ActionType GetType();

private:
	void DrawVertex();
	void EraseVertex();
};

#endif //_SHSELECTIONMOVEACTION_H