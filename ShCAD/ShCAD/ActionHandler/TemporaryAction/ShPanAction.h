
#ifndef _SHPANACTION_H
#define _SHPANACTION_H

#include "ShTemporaryAction.h"

class ShPanAction : public ShTemporaryAction {

private:
	double prevX;
	double prevY;

public:
	ShPanAction(ShCADWidget *widget);
	~ShPanAction();

	virtual void mouseMidPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);
	virtual void mouseReleaseEvent(ShActionData &data);

	virtual ActionType getType();

	virtual QCursor getCursorShape();

};

#endif //_SHPANACTION_H