

#ifndef _SHSUBDRAWLINEACTION_H
#define _SHSUBDRAWLINEACTION_H

#include "ShVariable.h"

class QMouseEvent;
class ShDrawLineAction;
class ShGraphicView;
class ShSubDrawLineAction {

protected:
	ShDrawLineAction *drawLineAction;
	ShGraphicView *view;
public:
	ShSubDrawLineAction(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	virtual ~ShSubDrawLineAction() = 0;

	virtual void MousePressEvent(QMouseEvent *event) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event, DrawType &drawType) = 0;
};

class ShSubDrawLineAction_Default : public ShSubDrawLineAction {

public:
	ShSubDrawLineAction_Default(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	~ShSubDrawLineAction_Default();

	virtual void MousePressEvent(QMouseEvent *event);
	virtual void MouseMoveEvent(QMouseEvent *event, DrawType &drawType);

};

#endif //_SHSUBDRAWLINEACTION_H