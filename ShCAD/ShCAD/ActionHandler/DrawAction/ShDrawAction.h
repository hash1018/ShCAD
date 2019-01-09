

#ifndef _SHDRAWACTION_H
#define _SHDRAWACTION_H

#include "ActionHandler\ShActionHandler.h"

class ShDrawAction : public ShActionHandler {

public:
	ShDrawAction(ShGraphicView *graphicView);
	virtual ~ShDrawAction() = 0;

	

};

#endif //_SHDRAWACTION_H