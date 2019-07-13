
#ifndef _SHTEMPORARYACTION_H
#define _SHTEMPORARYACTOPN_H

#include "ActionHandler\ShActionHandler.h"

class ShTemporaryAction : public ShActionHandler {

protected:
	ShActionHandler *previousAction;

public:
	ShTemporaryAction(ShCADWidget *widget, ShActionHandler *previousAction);
	virtual ~ShTemporaryAction() = 0;

protected:
	void returnToPrevious();

};

#endif //_SHTEMPORARYACTION_H