
#ifndef _SHMODIFYROTATEACTION_H
#define _SHMODIFYROTATEACTION_H

#include "ShModifyAction.h"

class ShModifyRotateAction : public ShModifyAction {

private:
	double prevAngle;

public:
	ShModifyRotateAction(ShCADWidget *widget);
	~ShModifyRotateAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseRightPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();


	virtual void invalidate(ShPoint3d &point);

	virtual void finishSelectingEntities();

protected:
	virtual void trigger(const ShPoint3d &point);
};

#endif //_SHMODIFYROTATEACTION_H