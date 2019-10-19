
#ifndef _SHMODIFYOFFSETACTION_H
#define _SHMODIFYOFFSETACTION_H

#include "ShModifyAction.h"

class ShModifyOffsetAction : public ShModifyAction {

public:
	ShModifyOffsetAction(ShCADWidget *widget);
	~ShModifyOffsetAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();

	virtual void finishSelectingEntities();

	virtual void invalidate(ShPoint3d &point);

protected:
	virtual void trigger(const ShPoint3d &point);
};

#endif //_SHMODIFYOFFSETACTION_H