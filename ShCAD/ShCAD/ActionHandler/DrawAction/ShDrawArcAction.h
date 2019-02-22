



#ifndef _SHDRAWARCACTION_H
#define _SHDRAWARCACTION_H

#include "ShDrawAction.h"

class ShDrawArcAction : public ShDrawAction {

	friend class ShDrawArcMethod;

public:
	enum Status {
		PickedNothing,
		PickedCenter,
		PickedStart,
		PickedFirstPoint,
		PickedSecondPoint,
	};
	enum DrawMethod {
		CenterStartEnd,
		StartEndRadius,
		ThreePoint,
	};

private:
	Status status;
	DrawMethod drawMethod;

public:
	ShDrawArcAction(ShGraphicView *graphicView);
	~ShDrawArcAction();

	virtual void MousePressEvent(QMouseEvent *event);
	virtual void MouseMoveEvent(QMouseEvent *event);
	virtual void KeyPressEvent(QKeyEvent *event);

	virtual ActionType GetType();
	virtual void ApplyOrthogonalShape(bool isOrthogonalModeOn);
	virtual void SetActionHeadTitle();
};


#include "ActionHandler\SubActionHandler\ShSubActionHandler.h"
class ShDrawArcMethod;
class ShDrawArcProxy : public ShSubIndividualAction {

private:
	ShDrawArcMethod *drawArcMethod;

public:
	ShDrawArcProxy(ShDrawArcAction *drawArcAction, ShGraphicView *view);
	~ShDrawArcProxy();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo &info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info);

};


class ShDrawArcMethod {

protected:
	ShDrawArcAction *drawArcAction;
	ShGraphicView *view;

public:
	ShDrawArcMethod(ShDrawArcAction *drawArcAction, ShGraphicView *view);
	virtual ~ShDrawArcMethod() = 0;

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo& info) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info) = 0;

protected:
	inline ShDrawArcAction::Status& GetStatus() const { return this->drawArcAction->status; }
	void AddEntity(ShEntity *newEntity, const QString& commandText) {
		this->drawArcAction->AddEntity(newEntity, commandText);
	}
	void SetDrawMethod(ShDrawArcAction::DrawMethod drawMethod) { this->drawArcAction->drawMethod = drawMethod; }

};

class ShDrawArcMethod_CenterStartEnd : public ShDrawArcMethod {

public:
	ShDrawArcMethod_CenterStartEnd(ShDrawArcAction *drawArcAction, ShGraphicView *view);
	~ShDrawArcMethod_CenterStartEnd();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo& info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info);

};

class ShDrawArcMethod_StartEndRadius : public ShDrawArcMethod {

public:
	ShDrawArcMethod_StartEndRadius(ShDrawArcAction *drawArcAction, ShGraphicView *view);
	~ShDrawArcMethod_StartEndRadius();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo& info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info);

};


class ShDrawArcMethod_ThreePoint : public ShDrawArcMethod {

public:
	ShDrawArcMethod_ThreePoint(ShDrawArcAction *drawArcAction, ShGraphicView *view);
	~ShDrawArcMethod_ThreePoint();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo& info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info);

};


#endif //_SHDRAWARCACTION_H