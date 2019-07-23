
#ifndef _SHDRAWACTION_H
#define _SHDRAWACTION_H

#include "ActionHandler\ShActionHandler.h"

class ShAddEntityTransaction;
class ShDrawAction : public ShActionHandler {

protected:
	ShAddEntityTransaction *addTransaction;

public:
	ShDrawAction(ShCADWidget *widget);
	virtual ~ShDrawAction() = 0;

	virtual QCursor getCursorShape();

protected:
	void addEntity(ShEntity *newEntity, const QString &type);
};

#endif //_SHDRAWACTION_H