

#ifndef _SHSELECTIONMOVEACTION_H
#define _SHSELECTIONMOVEACTION_H

#include "ActionHandler\TemporaryAction\ShTemporaryAction.h"
#include <qlist.h>
#include "ShPoint.h"

class ShEntity;
class ShStretchData;
class ShStretchTemporaryAction : public ShTemporaryAction {

private:
	ShPoint3d vertex;
	QList<ShEntity*> entitiesToStretch;
	QList<ShStretchData*> stretchDataList;

public:
	ShStretchTemporaryAction(ShGraphicView *graphicView,
		const QList<ShEntity*>& entitiesToStretch, const QList<ShStretchData*>& stretchDataList, ShPoint3d vertex);
	ShStretchTemporaryAction(ShGraphicView *graphicView, ShActionHandler *previousAction,
		const QList<ShEntity*>& entitiesToStretch, const QList<ShStretchData*>& stretchDataList, ShPoint3d vertex);
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