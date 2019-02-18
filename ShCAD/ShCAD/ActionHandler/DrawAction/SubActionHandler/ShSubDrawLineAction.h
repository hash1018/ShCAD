

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
	ShDrawLineDecorator *parent;

public:
	ShSubDrawLineAction(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	ShSubDrawLineAction(const ShSubDrawLineAction& other);
	virtual ~ShSubDrawLineAction() = 0;

	virtual void MousePressEvent(QMouseEvent *event, ShPoint3d point) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event, ShPoint3d point, DrawType& drawType) = 0;


	virtual void Draw(QPainter *painter) = 0;
	//virtual void SetObjectSnap(ObjectSnap objectSnap) {}

	virtual void Decorate(ShDrawLineDecorator *drawLineDecorator) = 0;
	virtual ShSubDrawLineAction* Clone() = 0;
	void SetParent(ShDrawLineDecorator *parent) { this->parent = parent; }

protected:
	inline ShDrawLineAction::Status& GetStatus() const { return this->drawLineAction->status; }
	void SetStatus(ShDrawLineAction::Status status) { this->drawLineAction->status = status; }
	inline ShDrawLineAction::DrawMethod& GetDrawMethod() const { return this->drawLineAction->drawMethod; }
	void SetDrawMethod(ShDrawLineAction::DrawMethod drawMethod) { this->drawLineAction->drawMethod = drawMethod; }
	
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
	virtual void Draw(QPainter *painter) {}
	virtual void Decorate(ShDrawLineDecorator *drawLineDecorator);
};


//Leaf class
class ShDrawLineMethod_Default : public ShDrawLineMethod {

public:
	ShDrawLineMethod_Default(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	ShDrawLineMethod_Default(const ShDrawLineMethod_Default& other);
	~ShDrawLineMethod_Default();

	virtual void MousePressEvent(QMouseEvent *event, ShPoint3d point);
	virtual void MouseMoveEvent(QMouseEvent *event, ShPoint3d point, DrawType& drawType);

	
	virtual ShDrawLineMethod_Default* Clone();
};

class ShDrawLineMethod_Perpendicular : public ShDrawLineMethod {
	
	friend class ShDrawLineDecorator_SnapMode_Perpendicular;
private:
	ShEntity* perpendicularBaseEntity;

public:
	ShDrawLineMethod_Perpendicular(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	ShDrawLineMethod_Perpendicular(ShDrawLineAction *drawLineAction, ShGraphicView *view,
		ShEntity *perpendicularBaseEntity);
	ShDrawLineMethod_Perpendicular(const ShDrawLineMethod_Perpendicular& other);
	~ShDrawLineMethod_Perpendicular();

	virtual void MousePressEvent(QMouseEvent *event, ShPoint3d point);
	virtual void MouseMoveEvent(QMouseEvent *event, ShPoint3d point, DrawType& drawType);

	virtual ShDrawLineMethod_Perpendicular* Clone();

};

/////////////////////////////////////////////////////////////////////////////////////////////////

//Decorator pattern.
class ShDrawLineDecorator : public ShSubDrawLineAction {

protected:
	ShSubDrawLineAction *child;

public:
	ShDrawLineDecorator(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	ShDrawLineDecorator(const ShDrawLineDecorator& other);
	virtual ~ShDrawLineDecorator() = 0;

	void SetChild(ShSubDrawLineAction *child);
	inline ShSubDrawLineAction* GetChild() const { return this->child; }


};


class ShObjectSnapState;
class ShDrawLineDecorator_SnapMode : public ShDrawLineDecorator {

protected:
	ObjectSnap objectSnap;
	ShObjectSnapState *objectSnapState;

public:
	ShDrawLineDecorator_SnapMode(ShDrawLineAction *drawLineAction, ShGraphicView *view, 
		ObjectSnap objectSnap);
	ShDrawLineDecorator_SnapMode(const ShDrawLineDecorator_SnapMode& other);
	~ShDrawLineDecorator_SnapMode();

	virtual void MousePressEvent(QMouseEvent *event, ShPoint3d point);
	virtual void MouseMoveEvent(QMouseEvent *event, ShPoint3d point, DrawType& drawType);

	virtual void Draw(QPainter *painter);
	virtual void Decorate(ShDrawLineDecorator *drawLineDecorator);

	virtual ShDrawLineDecorator_SnapMode* Clone();
};

class ShDrawLineDecorator_SnapMode_Perpendicular : public ShDrawLineDecorator_SnapMode {

public:
	ShDrawLineDecorator_SnapMode_Perpendicular(ShDrawLineAction *drawLineAction,
		ShGraphicView *view, ObjectSnap objectSnap);
	ShDrawLineDecorator_SnapMode_Perpendicular(const ShDrawLineDecorator_SnapMode_Perpendicular& other);
	~ShDrawLineDecorator_SnapMode_Perpendicular();

	virtual void MousePressEvent(QMouseEvent *event, ShPoint3d point);
	virtual void MouseMoveEvent(QMouseEvent *event, ShPoint3d point, DrawType& drawType);

	virtual ShDrawLineDecorator_SnapMode_Perpendicular* Clone();
};

class ShLine;
class ShDrawLineDecorator_Orthogonal : public ShDrawLineDecorator {

public:
	ShDrawLineDecorator_Orthogonal(ShDrawLineAction *drawLineAction, ShGraphicView *view);
	ShDrawLineDecorator_Orthogonal(const ShDrawLineDecorator_Orthogonal& other);
	~ShDrawLineDecorator_Orthogonal();

	virtual void MousePressEvent(QMouseEvent *event, ShPoint3d point);
	virtual void MouseMoveEvent(QMouseEvent *event, ShPoint3d point, DrawType& drawType);
	virtual void Draw(QPainter *painter);
	virtual void Decorate(ShDrawLineDecorator *drawLineDecorator);

	virtual ShDrawLineDecorator_Orthogonal* Clone();

private:
	void GetOrthogonal(double x, double y, double mouseX, double mouseY, double &orthX, double &orthY);
	void ApplyLineEndPointToOrthogonal(ShLine *line);
	void ApplyLineEndPointToMouse(ShLine *line);
};



#endif //_SHSUBDRAWLINEACTION_H