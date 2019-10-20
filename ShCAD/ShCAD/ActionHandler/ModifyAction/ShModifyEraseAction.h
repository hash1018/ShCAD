
#ifndef _SHMODIFYERASEACTION_H
#define _SHMODIFYERASEACTION_H

#include "ShModifyAction.h"

class ShModifyEraseAction : public ShModifyAction {

public:
	enum Status {
		SelectingEntities,

	};

private:
	Status status;

public:
	ShModifyEraseAction(ShCADWidget *widget);
	~ShModifyEraseAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseRightPressEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual QCursor getCursorShape();

	virtual void finishSelectingEntities();

};

#endif //_SHMODIFYERASEACTION_H