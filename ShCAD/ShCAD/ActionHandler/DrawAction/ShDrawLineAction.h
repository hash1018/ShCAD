

#ifndef _SHDRAWLINEACTION_H
#define _SHDRAWLINEACTION_H

#include "ShDrawAction.h"

class ShDrawLineAction : public ShDrawAction {

public:
	enum Status {
		PickedNothing, // no point picked. About to pick start.
		PickedStart    // start point already picked. About to pick end.
	};

	enum DrawMethod {
		Default,
		Perpendicular,
	};

private:
	Status status;
	DrawMethod drawMethod;
	//ShKeyHandler<ShDrawLineAction> *keyHandler;
	//ShKeyHandler *keyHandler;

public:
	ShDrawLineAction(ShCADWidget *widget);
	~ShDrawLineAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();

	virtual QString getHeadTitle();

	void temp();
};


#endif //_SHDRAWLINEACTION_H