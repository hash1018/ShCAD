
#ifndef _SHPANMOVEACTION_H
#define _SHPANMOVEACTION_H

#include "ShTemporaryAction.h"

class ShPanMoveAction : public ShTemporaryAction {

private:
	double prevX;
	double prevY;

public:
	ShPanMoveAction(ShCADWidget *widget, ShActionHandler *previousAction);
	~ShPanMoveAction();

	virtual void mouseMidPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);
	virtual void mouseReleaseEvent(ShActionData &data);

	virtual ActionType getType();

	virtual QCursor getCursorShape();

};

#endif //_SHPANMOVEACTION_H