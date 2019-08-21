
#ifndef _SHMODIFYMOVEACTION_H
#define _SHMODIFYMOVEACTION_H

#include "ShModifyAction.h"

class ShModifyMoveAction : public ShModifyAction {

public:
	ShModifyMoveAction(ShCADWidget *widget);
	~ShModifyMoveAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseRightPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();
	

	virtual void invalidate(ShPoint3d point);

	virtual void finishSelectingEntities();

};

#endif //_SHMODIFYMOVEACTION_H