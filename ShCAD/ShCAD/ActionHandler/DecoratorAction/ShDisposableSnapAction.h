

#ifndef _SHDISPOSABLESNAPACTION_H
#define _SHDISPOSABLESNAPACTION_H

#include "ShDecoratorAction.h"

class ShSearchSnapPointStrategy;

class ShDisposableSnapAction : public ShDecoratorAction {

protected:
	ShSearchSnapPointStrategy *strategy;

public:
	ShDisposableSnapAction(ShCADWidget *widget, ShActionHandler *actionHandler, ObjectSnap objectSnap, ShDecoratorAction *child = nullptr);
	virtual ~ShDisposableSnapAction() = 0;

	virtual void keyPressEvent(ShActionData &data);
	virtual void draw(QPainter *painter);

protected:
	void finishDisposableSnap();
	void sendFailMessage();

};

//////////////////////////////////////////////////////////////////

class ShDisposableSnapAction_General : public ShDisposableSnapAction {

public:
	ShDisposableSnapAction_General(ShCADWidget *widget, ShActionHandler *actionHandler, ObjectSnap objectSnap, ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction_General();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void invalidate(ShPoint3d &point);

};

//////////////////////////////////////////////////////////////////

class ShDisposableSnapAction__Intersection : public ShDisposableSnapAction {

public:
	ShDisposableSnapAction__Intersection(ShCADWidget *widget, ShActionHandler *actionHandler, ObjectSnap objectSnap, ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction__Intersection();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void invalidate(ShPoint3d &point);
};

//////////////////////////////////////////////////////////////////

class ShDisposableSnapAction_Perpendicular : public ShDisposableSnapAction {

public:
	ShDisposableSnapAction_Perpendicular(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction_Perpendicular();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void invalidate(ShPoint3d &point);

};

///////////////////////////////////////////////////////////////////

class ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing : public ShDisposableSnapAction {

public:
	ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing(ShCADWidget *widget, ShActionHandler *actionHandler,
		ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void invalidate(ShPoint3d &point);

};

/////////////////////////////////////////////////////////////////////

//** this case is that line entity is being drawn in the way pervious Perpendicular snap mode applied ,
//** current snap mode is perpendicular as well.
//** line entity only can be added when both baseSnapPerpendicular entities are parallel.
class ShDisposableSnapAction_DrawLineActionPerPer : public ShDisposableSnapAction {

public:
	ShDisposableSnapAction_DrawLineActionPerPer(ShCADWidget *widget, ShActionHandler *actionHandler,
		ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction_DrawLineActionPerPer();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void invalidate(ShPoint3d &point);

};


#endif //_SHDISPOSABLESNAPACTION_H