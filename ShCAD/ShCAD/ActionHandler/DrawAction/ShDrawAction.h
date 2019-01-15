

#ifndef _SHDRAWACTION_H
#define _SHDRAWACTION_H

#include "ActionHandler\ShActionHandler.h"

class ShEntity;
class ShDrawAction : public ShActionHandler {

public:
	ShDrawAction(ShGraphicView *graphicView);
	virtual ~ShDrawAction() = 0;

	virtual QCursor GetCursorShape();

protected:
	void AddEntity(ShEntity* newEntity);
	

};

#endif //_SHDRAWACTION_H