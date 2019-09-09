

#ifndef _SHDISPOSABLEPERSNAPLINEACTION_H
#define _SHDISPOSABLEPERSNAPLINEACTION_H

#include "ActionHandler\DecoratorAction\ShDisposableSnapAction.h"

class ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing : public ShDisposableSnapAction {

private:
	ShEntity *basePerpendicularEntity;
public:
	ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing(ShCADWidget *widget, ShActionHandler *actionHandler,
		ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void draw(QPainter *painter);
	virtual void invalidate(ShDecoratorActionData &data);

protected:
	virtual bool search(const ShPoint3d &point);
};

/////////////////////////////////////////////////////////////////////

//** this case is that line entity is being drawn in the way pervious Perpendicular snap mode applied ,
//** current snap mode is perpendicular as well.
//** line entity only can be added when both baseSnapPerpendicular entities are parallel.
class ShDisposableSnapAction_DrawLineActionPerPer : public ShDisposableSnapAction {

private:
	ShEntity *basePerpendicularEntity;

public:
	ShDisposableSnapAction_DrawLineActionPerPer(ShCADWidget *widget, ShActionHandler *actionHandler,
		ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction_DrawLineActionPerPer();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void draw(QPainter *painter);
	virtual void invalidate(ShDecoratorActionData &data);

protected:
	virtual bool search(const ShPoint3d &point);
};

#endif //_SHDISPOSABLEPERSNAPLINEACTION_H