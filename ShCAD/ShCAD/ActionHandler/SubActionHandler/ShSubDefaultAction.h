

#ifndef _SHSUBDEFAULTACTION_H
#define _SHSUBDEFAULTACTION_H

#include "ShPoint.h"
class ShDefaultAction;
class QMouseEvent;
class ShGraphicView;


class ShSubDefaultAction {

protected:
	ShDefaultAction *defaultAction;
	ShGraphicView *view;

public:
	ShSubDefaultAction(ShDefaultAction *defaultAction, ShGraphicView *view);
	virtual ~ShSubDefaultAction() = 0;


	virtual void MousePressEvent(QMouseEvent *event) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event) = 0;

};

class ShSubDefaultAction_Default : public ShSubDefaultAction {

public:
	ShSubDefaultAction_Default(ShDefaultAction *defaultAction, ShGraphicView *view);
	~ShSubDefaultAction_Default();

	void MousePressEvent(QMouseEvent *event);
	void MouseMoveEvent(QMouseEvent *event);

};


// This is the class for preparing for selection move.
class ShSubDefaultAction_MouseIsInEntityVertex : public ShSubDefaultAction {

private:
	ShPoint3d vertex;

public:
	ShSubDefaultAction_MouseIsInEntityVertex(ShDefaultAction *defaultAction, ShGraphicView *view,
		const ShPoint3d& vertex);
	~ShSubDefaultAction_MouseIsInEntityVertex();

	void MousePressEvent(QMouseEvent *event);
	void MouseMoveEvent(QMouseEvent *event);

private:
	void DrawVertex();
	void EraseVertex();

};

#endif //_SHSUBDEFAULTACTION_H