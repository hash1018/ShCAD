
#ifndef _SHTEMPORARYACTION_H
#define _SHTEMPORARYACTION_H

#include "ActionHandler\ShActionHandler.h"

class ShTemporaryAction : public ShActionHandler {

protected:
	ShActionHandler *previousAction;

public:
	ShTemporaryAction(ShCADWidget *widget);
	virtual ~ShTemporaryAction() = 0;

	void setPreviousAction(ShActionHandler *previousAction);
	inline ShActionHandler *getPreviousAction() const { return this->previousAction; }

	virtual ActionType getTypeIgnoringTemp();

protected:
	void returnToPrevious();

};

#endif //_SHTEMPORARYACTION_H