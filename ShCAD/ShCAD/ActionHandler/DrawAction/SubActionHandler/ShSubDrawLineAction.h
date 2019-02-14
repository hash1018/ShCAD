

#ifndef _SHSUBDRAWLINEACTION_H
#define _SHSUBDRAWLINEACTION_H


#include "ActionHandler\DrawAction\ShDrawLineAction.h"
class QMouseEvent;
class ShDrawLineAction;
class ShDrawLineDecorator;
class ShGraphicView;

class ShSubDrawLineAction {

	//ShDrawLineAction is a friend class.
protected:
	ShDrawLineAction *drawLineAction;
	ShGraphicView *view;
	ShPoint3d point;

public:
	ShSubDrawLineAction(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	ShSubDrawLineAction(const ShSubDrawLineAction& other);
	virtual ~ShSubDrawLineAction() = 0;

	virtual void MousePressEvent(QMouseEvent *event) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event, DrawType& drawType) = 0;


	virtual void Draw(QPainter *painter) {}
	void SetPoint(const ShPoint3d& point) { this->point = point; }
	virtual void SetObjectSnap(ObjectSnap objectSnap) {}

	virtual void Decorate(ShDrawLineDecorator *drawLineDecorator) = 0;

protected:
	inline ShDrawLineAction::Status& GetStatus() const { return this->drawLineAction->status; }
	inline ShPoint3d& GetStart() const { return this->drawLineAction->start; }
	inline ShPoint3d& GetEnd() const { return this->drawLineAction->end; }
	void SetStatus(ShDrawLineAction::Status status) { this->drawLineAction->status = status; }
	void SetStart(ShPoint3d start) { this->drawLineAction->start = start; }
	void SetEnd(ShPoint3d end) { this->drawLineAction->end = end; }
	
	void AddEntity(ShEntity *newEntity, const QString& commandText) {
		this->drawLineAction->AddEntity(newEntity, commandText);
	}

};


//Leaf class
class ShDrawLineMethod : public ShSubDrawLineAction {

public:
	ShDrawLineMethod(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	ShDrawLineMethod(const ShDrawLineMethod& other);
	virtual ~ShDrawLineMethod() = 0;

	
};


//Leaf class
class ShDrawLineMethod_Default : public ShDrawLineMethod {

public:
	ShDrawLineMethod_Default(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	ShDrawLineMethod_Default(const ShDrawLineMethod_Default& other);
	~ShDrawLineMethod_Default();

	virtual void MousePressEvent(QMouseEvent *event);
	virtual void MouseMoveEvent(QMouseEvent *event, DrawType& drawType);

	virtual void Decorate(ShDrawLineDecorator *drawLineDecorator);
};


/////////////////////////////////////////////////////////////////////////////////////////////////

//Decorator pattern.
class ShDrawLineDecorator : public ShSubDrawLineAction {

protected:
	ShSubDrawLineAction *subDrawLineAction;

public:
	ShDrawLineDecorator(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	ShDrawLineDecorator(ShDrawLineAction *drawLineAction, ShGraphicView *view,
		ShSubDrawLineAction *subDrawLineAcion);
	ShDrawLineDecorator(const ShDrawLineDecorator& other);
	virtual ~ShDrawLineDecorator() = 0;

	virtual void SetSubAction(ShSubDrawLineAction *subAction);
protected:
	// this function lets the subAction of an instance of the decorator class 
	// becomes currentSubAction of the ShDrawLineAction.
	void TakeOffBoundarySubAction();

};


class ShObjectSnapContext;
class ShDrawLineDecorator_SnapMode : public ShDrawLineDecorator {

private:
	ObjectSnap objectSnap;
	ShObjectSnapContext *objectSnapContext;

public:
	ShDrawLineDecorator_SnapMode(ShDrawLineAction *drawLineAction, ShGraphicView *view, 
		ObjectSnap objectSnap);
	ShDrawLineDecorator_SnapMode(ShDrawLineAction *drawLineAction, ShGraphicView *view,
		ShDrawLineMethod *subDrawLineAction, ObjectSnap objectSnap);
	ShDrawLineDecorator_SnapMode(const ShDrawLineDecorator_SnapMode& other);
	~ShDrawLineDecorator_SnapMode();

	virtual void MousePressEvent(QMouseEvent *event);
	virtual void MouseMoveEvent(QMouseEvent *event, DrawType& drawType);

	virtual void Draw(QPainter *painter);
	virtual void Decorate(ShDrawLineDecorator *drawLineDecorator);
};


#endif //_SHSUBDRAWLINEACTION_H