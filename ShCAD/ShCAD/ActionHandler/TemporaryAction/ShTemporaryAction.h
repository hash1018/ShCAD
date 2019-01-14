

#ifndef _SHTEMPORARYACTION_H
#define _SHTEMPORARYACTION_H

/*  Base class that is used only temporary period.
    graphicView is currently set to origianl Action such as default, drawing Line , modifying something , etc,
	This class help origianl Action to do something expansion without changing current original Action.
	For example) zoomAction or panAction can be used while defaultAction is on.

*/

#include "ActionHandler\ShActionHandler.h"
class ShTemporaryAction : public ShActionHandler {

protected:
	ShActionHandler *previousAction;

public:
	ShTemporaryAction(ShGraphicView *graphicView, ShActionHandler *previousAction);
	virtual ~ShTemporaryAction() = 0;

protected:
	void ReturnToPrevious();
};

#endif //_SHTEMPORARYACTION_H