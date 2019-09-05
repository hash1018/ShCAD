
#ifndef _SHTEMPORARYSTRETCHACTION_H
#define _SHTEMPORARYSTRETCHACTION_H

#include "ShTemporaryAction.h"
#include <qlinkedlist.h>
#include "Data\ShPoint.h"

class ShEntity;
class ShStretchData;

class ShTemporaryStretchAction : public ShTemporaryAction {

private:
	ShPoint3d vertexPoint;
	QLinkedList<ShEntity*> possibleStretchEntities;
	QLinkedList<ShStretchData*> stretchDatas;
	bool createdPreview;

public:
	ShTemporaryStretchAction(ShCADWidget *widget, const ShPoint3d &vertexPoint, const QLinkedList<ShEntity*> &possibleStretchEntities,
		const QLinkedList<ShStretchData*> &stretchDatas);
	~ShTemporaryStretchAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QCursor getCursorShape();
	virtual void draw(QPainter *painter);

	virtual QString getHeadTitle();

	virtual void invalidate(ShPoint3d &point);
	virtual ShAvailableDraft getAvailableDraft();

	virtual ShPoint3d getLastBasePoint();
	virtual ShPoint3d getCurrentAboutToPickPoint();

protected:
	virtual void trigger(const ShPoint3d &point);

};

#endif //_SHTEMPORARYSTRETCHACTION_H