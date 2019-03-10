

#ifndef _SHACTIONHANDLERDECORATOR_H
#define _SHACTIONHANDLERDECORATOR_H

#include "ActionHandler\ShActionHandler.h"
#include "ShDraft.h"

class ShObjectSnapStrategy;
class ShActionDecoratorData{

private:
	bool snapClicked;

public:
	ShActionDecoratorData() : snapClicked(false) {}
	~ShActionDecoratorData() {}

	inline bool SnapClicked() const { return this->snapClicked; }
	void SetSnapClicked(bool clicked) { this->snapClicked = clicked; }
};


class ShActionHandlerDecorator {

protected:
	ShGraphicView *graphicView;
	ShActionHandler *actionHandler;
	ShActionHandlerDecorator *child;
	ShActionHandlerDecorator *parent;

public:
	ShActionHandlerDecorator(ShGraphicView *graphicView, ShActionHandler *actionHandler, ShActionHandlerDecorator *child = 0);
	virtual ~ShActionHandlerDecorator() = 0;

	virtual void MousePressEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);
	virtual void MouseReleaseEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);

	virtual ActionType GetType();
	virtual void Draw(QPainter *painter);

	void SetParent(ShActionHandlerDecorator *parent) { this->parent = parent; }
	inline ShActionHandlerDecorator* GetParent() const { return this->parent; }
	inline ShActionHandlerDecorator* GetChild() const { return this->child; }
};

class ShActionHandlerDecorator_Default : public ShActionHandlerDecorator {

public:
	ShActionHandlerDecorator_Default(ShGraphicView *graphicView, ShActionHandler *actionHandler, ShActionHandlerDecorator *child = 0);
	~ShActionHandlerDecorator_Default();

};

class ShActionHandlerDecorator_Draft : public ShActionHandlerDecorator {

public:
	ShActionHandlerDecorator_Draft(ShGraphicView *graphicView, ShActionHandler *actionHandler, ShActionHandlerDecorator *child = 0);
	virtual ~ShActionHandlerDecorator_Draft() = 0;


};

class ShActionHandlerDecorator_DisposableSnap : public ShActionHandlerDecorator_Draft {

protected:
	ShObjectSnapStrategy *objectSnapStrategy;

public:
	ShActionHandlerDecorator_DisposableSnap(ShGraphicView *graphicView, ShActionHandler *actionHandler, 
		ObjectSnap objectSnap, ShActionHandlerDecorator *child = 0);
	virtual ~ShActionHandlerDecorator_DisposableSnap() = 0;
	
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);
	virtual void Draw(QPainter *painter);

protected:
	void SendFailedMessage(ObjectSnap objectSnap);
};

//End,Mid,Center,Quadrant
class ShActionHandlerDecorator_DisposableSnap_General : public ShActionHandlerDecorator_DisposableSnap {

public:
	ShActionHandlerDecorator_DisposableSnap_General(ShGraphicView *graphicView, ShActionHandler *actionHandler,
		ObjectSnap objectSnap, ShActionHandlerDecorator *child = 0);
	~ShActionHandlerDecorator_DisposableSnap_General();

	virtual void MousePressEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);
	

};

class ShActionHandlerDecorator_DisposableSnap_Perpendicular : public ShActionHandlerDecorator_DisposableSnap {

public:
	ShActionHandlerDecorator_DisposableSnap_Perpendicular(ShGraphicView *graphicView, 
		ShActionHandler *actionHandler, ShActionHandlerDecorator *child = 0);
	~ShActionHandlerDecorator_DisposableSnap_Perpendicular();

	virtual void MousePressEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);
	
};


//Special case.
class ShDrawLineAction_DisposableSnap_Perpendicular_PickedNothing : public ShActionHandlerDecorator_DisposableSnap {

public:
	ShDrawLineAction_DisposableSnap_Perpendicular_PickedNothing(ShGraphicView *graphicView,
		ShActionHandler *actionHandler, ShActionHandlerDecorator *child = 0);
	~ShDrawLineAction_DisposableSnap_Perpendicular_PickedNothing();

	virtual void MousePressEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);
	

};

//** this case is that line entity is being drawn in the way pervious Perpendicular snap mode applied ,
//** current snap mode is perpendicular as well.
//** line entity only added when both baseSnapPerpendicular entities are parallel.
class ShDrawLineAction_DisposableSnap_Per_Per : public ShActionHandlerDecorator_DisposableSnap {

public:
	ShDrawLineAction_DisposableSnap_Per_Per(ShGraphicView *graphicView, ShActionHandler *actionHandler,
		ShActionHandlerDecorator *child = 0);
	~ShDrawLineAction_DisposableSnap_Per_Per();

	virtual void MousePressEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);
	

};


class ShActionHandlerDecorator_Orthogonal : public ShActionHandlerDecorator_Draft {

public:
	ShActionHandlerDecorator_Orthogonal(ShGraphicView *graphicView, ShActionHandler *actionHandler, ShActionHandlerDecorator *child = 0);
	~ShActionHandlerDecorator_Orthogonal();

	virtual void MousePressEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data, ShActionDecoratorData &decoratorData);

protected:
	void GetOrthogonal(double x, double y, double mouseX, double mouseY, double &orthX, double &orthY);
};



#endif //_SHACTIONHANDERDECORATOR_H
