

#ifndef _SHDRAWLINEACTION_H
#define _SHDRAWLINEACTION_H


#include "ShDrawAction.h"
#include "ShPoint.h"
class ShDrawLineAction : public ShDrawAction{
	
public:
	enum Status {
		PickedNothing, // no point picked. About to pick start.
		PickedStart    // start point already picked. About to pick end.
	};

private:
	Status status;
	ShPoint3d start;
	ShPoint3d end;

public:
	ShDrawLineAction(ShGraphicView *graphicView);
	~ShDrawLineAction();

	virtual void MousePressEvent(QMouseEvent *event);
	virtual void MouseMoveEvent(QMouseEvent *event);
	virtual void KeyPressEvent(QKeyEvent *event);


	virtual ActionType GetType();
};

#endif //_SHDRAWLINEACTION_H