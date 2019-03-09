

#ifndef _SHDRAWCIRCLEACTION_H
#define _SHDRAWCIRCLEACTION_H

#include "ShDrawAction.h"

class ShDrawCircleAction : public ShDrawAction {
	
	friend class ShDrawCircleMethod;

public:
	enum Status {
		PickedNothing,
		PickedCenter,
		PickedFirstPoint,
		PickedSecondPoint,
	};
	enum DrawMethod {
		CenterRadius,
		CenterDiameter,
		TwoPoint,
		ThreePoint,
	};

private:
	Status status;
	DrawMethod drawMethod;

public:
	ShDrawCircleAction(ShGraphicView *graphicView);
	~ShDrawCircleAction();

	virtual void MousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data);

	virtual ActionType GetType();
	//virtual void ApplyOrthogonalShape(bool isOrthogonalModeOn);
	virtual void SetActionHeadTitle();
};

/*

#include "ActionHandler\SubActionHandler\ShSubActionHandler.h"
class ShDrawCircleMethod;
class ShDrawCircleProxy : public ShSubIndividualAction {

private:
	ShDrawCircleMethod *drawCircleMethod;

public:
	ShDrawCircleProxy(ShDrawCircleAction *drawCircleAction, ShGraphicView *view);
	~ShDrawCircleProxy();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo &info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info);

};


class ShDrawCircleMethod {

protected:
	ShDrawCircleAction *drawCircleAction;
	ShGraphicView *view;

public:
	ShDrawCircleMethod(ShDrawCircleAction *drawCircleAction, ShGraphicView *view);
	virtual ~ShDrawCircleMethod() = 0;

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo& info) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info) = 0;

protected:
	inline ShDrawCircleAction::Status& GetStatus() const { return this->drawCircleAction->status; }
	void AddEntity(ShEntity *newEntity, const QString& commandText) {
		delete this->view->rubberBand;
		this->view->rubberBand = 0;
		this->drawCircleAction->AddEntity(newEntity, commandText);
	}
	void SetDrawMethod(ShDrawCircleAction::DrawMethod drawMethod) { this->drawCircleAction->drawMethod = drawMethod; }

};

class ShDrawCircleMethod_CenterRadius : public ShDrawCircleMethod {

public:
	ShDrawCircleMethod_CenterRadius(ShDrawCircleAction *drawCircleAction, ShGraphicView *view);
	~ShDrawCircleMethod_CenterRadius();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo& info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info);

};

class ShDrawCircleMethod_CenterDiameter : public ShDrawCircleMethod {

public:
	ShDrawCircleMethod_CenterDiameter(ShDrawCircleAction *drawCircleAction, ShGraphicView *view);
	~ShDrawCircleMethod_CenterDiameter();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo& info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info);

};

class ShDrawCircleMethod_TwoPoint : public ShDrawCircleMethod {

public:
	ShDrawCircleMethod_TwoPoint(ShDrawCircleAction *drawCircleAction, ShGraphicView *view);
	~ShDrawCircleMethod_TwoPoint();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo& info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info);

};

class ShDrawCircleMethod_ThreePoint : public ShDrawCircleMethod {

public:
	ShDrawCircleMethod_ThreePoint(ShDrawCircleAction *drawCircleAction, ShGraphicView *view);
	~ShDrawCircleMethod_ThreePoint();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo& info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo& info);

};

*/


#endif //_SHDRAWCIRCLEACTION_H