
#ifndef _SHMODIFYACTION_H
#define _SHMODIFYACTION_H

#include "ActionHandler\ShActionHandler.h"
class ShModifyAction : public ShActionHandler {

public:
	ShModifyAction(ShGraphicView *graphicView);
	virtual ~ShModifyAction() = 0;


};

#endif //_SHMODIFYACTION_H