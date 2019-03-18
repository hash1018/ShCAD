
#ifndef _SHMODIFYACTION_H
#define _SHMODIFYACTION_H

#include "ActionHandler\ShActionHandler.h"
class ShEntity;
class ShModifyAction : public ShActionHandler {

public:
	ShModifyAction(ShGraphicView *graphicView);
	virtual ~ShModifyAction() = 0;

protected:
	void DoFollowUpWithFoundEntity(ShEntity* foundEntity, Qt::KeyboardModifiers modifier);

};

#endif //_SHMODIFYACTION_H