

#ifndef _SHDISPOSABLESNAPACTION_H
#define _SHDISPOSABLESNAPACTION_H

#include "ShDecoratorAction.h"
class ShEntity;

class ShDisposableSnapAction : public ShDecoratorAction {

protected:
	ShPoint3d snap;
	bool valid;

public:
	ShDisposableSnapAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	virtual ~ShDisposableSnapAction() = 0;

	virtual void keyPressEvent(ShActionData &data);
	virtual void draw(QPainter *painter) = 0;

protected:
	void finishDisposableSnap();
	virtual void sendFailMessage();

};


//////////////////////////////////////////////////////////////////

class ShDisposableSnapAction_End : public ShDisposableSnapAction {

public:
	ShDisposableSnapAction_End(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction_End();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void draw(QPainter *painter);
	virtual void invalidate(ShDecoratorActionData &data);

protected:
	virtual bool search(const ShPoint3d &point);
};


//////////////////////////////////////////////////////////////////

class ShDisposableSnapAction_Mid : public ShDisposableSnapAction {

public:
	ShDisposableSnapAction_Mid(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction_Mid();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void draw(QPainter *painter);
	virtual void invalidate(ShDecoratorActionData &data);

protected:
	virtual bool search(const ShPoint3d &point);
};

//////////////////////////////////////////////////////////////////

class ShDisposableSnapAction_Center : public ShDisposableSnapAction {

public:
	ShDisposableSnapAction_Center(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction_Center();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void draw(QPainter *painter);
	virtual void invalidate(ShDecoratorActionData &data);

protected:
	virtual bool search(const ShPoint3d &point);
};

//////////////////////////////////////////////////////////////////

class ShDisposableSnapAction_Quadrant : public ShDisposableSnapAction {

public:
	ShDisposableSnapAction_Quadrant(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction_Quadrant();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void draw(QPainter *painter);
	virtual void invalidate(ShDecoratorActionData &data);

protected:
	virtual bool search(const ShPoint3d &point);
};

//////////////////////////////////////////////////////////////////

class ShDisposableSnapAction__Intersection : public ShDisposableSnapAction {

public:
	enum Status {
		PickedNothing,
		PickedBaseEntity,
	};

protected:
	ShEntity *firstBaseEntity;
	bool foundOnlyOne;
	Status status;

public:
	ShDisposableSnapAction__Intersection(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction__Intersection();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void draw(QPainter *painter);
	virtual void invalidate(ShDecoratorActionData &data);

protected:
	virtual bool search(const ShPoint3d &point);
	virtual void sendFailMessage();
};

//////////////////////////////////////////////////////////////////

class ShDisposableSnapAction_ApparentIntersection : public ShDisposableSnapAction__Intersection {

public:
	ShDisposableSnapAction_ApparentIntersection(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction_ApparentIntersection();

	virtual void draw(QPainter *painter);

};

//////////////////////////////////////////////////////////////////

class ShDisposableSnapAction_Perpendicular : public ShDisposableSnapAction {

public:
	ShDisposableSnapAction_Perpendicular(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction_Perpendicular();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void draw(QPainter *painter);
	virtual void invalidate(ShDecoratorActionData &data);

private:
	bool search(const ShPoint3d &point, double perpendicularX, double perpendicularY);
};

//////////////////////////////////////////////////////////////////

class ShDisposableSnapAction_Node : public ShDisposableSnapAction {

public:
	ShDisposableSnapAction_Node(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction_Node();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void draw(QPainter *painter);
	virtual void invalidate(ShDecoratorActionData &data);

protected:
	virtual bool search(const ShPoint3d &point);
};

#endif //_SHDISPOSABLESNAPACTION_H