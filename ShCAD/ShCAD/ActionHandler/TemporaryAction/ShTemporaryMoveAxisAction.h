
#ifndef _SHTEMPORARYMOVEAXISACTION_H
#define _SHTEMPORARYMOVEAXISACTION_H

#include "ShTemporaryAction.h"

class ShTemporaryMoveAxisAction : public ShTemporaryAction {

private:
	bool createdPreview;

public:
	ShTemporaryMoveAxisAction(ShCADWidget *widget);
	~ShTemporaryMoveAxisAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QCursor getCursorShape();
	virtual void draw(QPainter *painter);

	virtual QString getHeadTitle();

	virtual void invalidate(ShPoint3d &point);
	virtual ShAvailableDraft getAvailableDraft();

protected:
	virtual void trigger(const ShPoint3d &point);

};

#endif //_SHTEMPORARYMOVEAXISACTION_H