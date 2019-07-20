
#ifndef _SHDRAWACTION_H
#define _SHDRAWACTION_H

#include "ActionHandler\ShActionHandler.h"

class ShDrawAction : public ShActionHandler {

public:
	ShDrawAction(ShCADWidget *widget);
	virtual ~ShDrawAction() = 0;

	virtual QCursor getCursorShape();

};

#endif //_SHDRAWACTION_H