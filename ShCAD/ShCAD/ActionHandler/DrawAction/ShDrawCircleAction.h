

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
	ShDrawCircleMethod *drawCircleMethod;

public:
	ShDrawCircleAction(ShGraphicView *graphicView);
	~ShDrawCircleAction();

	virtual void MousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data);

	virtual ActionType GetType();

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);

};

class ShDrawCircleMethod {

protected:
	ShDrawCircleAction *drawCircleAction;
	ShGraphicView *view;

public:
	ShDrawCircleMethod(ShDrawCircleAction *drawCircleAction, ShGraphicView *view);
	virtual ~ShDrawCircleMethod() = 0;

	virtual void MousePressEvent(QMouseEvent *event, ShActionData& data) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data) = 0;

	virtual void ApplyOrthogonalShape(bool on) = 0;
	virtual QString GetActionHeadTitle() = 0;
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data) = 0;

protected:
	inline ShDrawCircleAction::Status& GetStatus() const { return this->drawCircleAction->status; }
	void AddEntityAndFinish(ShEntity *newEntity, const QString& commandText) {
		this->drawCircleAction->AddEntityAndFinish(newEntity, commandText);
	}
	void GetOrthogonal(double x, double y, double mouseX, double mouseY, double &orthX, double &orthY) {
		this->drawCircleAction->GetOrthogonal(x, y, mouseX, mouseY, orthX, orthY);
	}
};

class ShDrawCircleMethod_CenterRadius : public ShDrawCircleMethod {

public:
	ShDrawCircleMethod_CenterRadius(ShDrawCircleAction *drawCircleAction, ShGraphicView *view);
	~ShDrawCircleMethod_CenterRadius();

	virtual void MousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);
};

class ShDrawCircleMethod_CenterDiameter : public ShDrawCircleMethod {

public:
	ShDrawCircleMethod_CenterDiameter(ShDrawCircleAction *drawCircleAction, ShGraphicView *view);
	~ShDrawCircleMethod_CenterDiameter();

	virtual void MousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);
};

class ShDrawCircleMethod_TwoPoint : public ShDrawCircleMethod {

public:
	ShDrawCircleMethod_TwoPoint(ShDrawCircleAction *drawCircleAction, ShGraphicView *view);
	~ShDrawCircleMethod_TwoPoint();

	virtual void MousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);
};

class ShDrawCircleMethod_ThreePoint : public ShDrawCircleMethod {

public:
	ShDrawCircleMethod_ThreePoint(ShDrawCircleAction *drawCircleAction, ShGraphicView *view);
	~ShDrawCircleMethod_ThreePoint();

	virtual void MousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);
};

#endif //_SHDRAWCIRCLEACTION_H