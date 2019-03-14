



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
		PickedEnd,
	};
	enum DrawMethod {
		ThreePoint,
		
		StartCenterEnd,
		StartCenterAngle,
		StartCenterLength,
		
		StartEndAngle,
		StartEndDirection,
		StartEndRadius,

		CenterStartEnd,
		CenterStartAngle,
		CenterStartLength,
	
	};

private:
	Status status;
	DrawMethod drawMethod;
	ShDrawArcMethod *drawArcMethod;

public:
	ShDrawArcAction(ShGraphicView *graphicView, ShDrawArcAction::DrawMethod drawMethod = ThreePoint);
	~ShDrawArcAction();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data);

	virtual ActionType GetType();

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);

private:
	void SetDrawMethod(DrawMethod drawMethod);

};

///////////////////////////////////////////////////////////////////////////////////////

class ShDrawArcMethod {

protected:
	ShDrawArcAction *drawArcAction;
	ShGraphicView *view;

public:
	ShDrawArcMethod(ShDrawArcAction *drawArcAction, ShGraphicView *view);
	virtual ~ShDrawArcMethod() = 0;

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data) = 0;

	virtual void ApplyOrthogonalShape(bool on) = 0;
	virtual QString GetActionHeadTitle() = 0;
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data) = 0;

protected:
	inline ShDrawArcAction::Status& GetStatus() const { return this->drawArcAction->status; }
	void AddEntityAndFinish(ShEntity *newEntity, const QString& commandText) {
		this->drawArcAction->AddEntityAndFinish(newEntity, commandText);
	}
	void GetOrthogonal(double x, double y, double mouseX, double mouseY, double &orthX, double &orthY) {
		this->drawArcAction->GetOrthogonal(x, y, mouseX, mouseY, orthX, orthY);
	}
	
};

////////////////////////////////////////////////////////////////////////////////////

class ShArcData;
class ShDrawArcMethod_ThreePoint : public ShDrawArcMethod {

private:
	ShPoint3d first;
	ShPoint3d second;

public:
	ShDrawArcMethod_ThreePoint(ShDrawArcAction *drawArcAction, ShGraphicView *view);
	~ShDrawArcMethod_ThreePoint();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);

private:
	bool GetArcDataWithThreePoint(const ShPoint3d& first, const ShPoint3d& second, const ShPoint3d& third,
		ShArcData &data);
};

/////////////////////////////////////////////////////////////////////////////////////

class ShDrawArcMethod_StartCentertEnd : public ShDrawArcMethod {

private:
	ShPoint3d start;
	ShPoint3d center;

public:
	ShDrawArcMethod_StartCentertEnd(ShDrawArcAction *drawArcAction, ShGraphicView *view);
	~ShDrawArcMethod_StartCentertEnd();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);

};

class ShDrawArcMethod_StartCentertAngle : public ShDrawArcMethod {

private:
	ShPoint3d start;
	ShPoint3d center;

public:
	ShDrawArcMethod_StartCentertAngle (ShDrawArcAction *drawArcAction, ShGraphicView *view);
	~ShDrawArcMethod_StartCentertAngle();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);

};


class ShDrawArcMethod_StartCentertLength : public ShDrawArcMethod {

private:
	ShPoint3d start;
	ShPoint3d center;

public:
	ShDrawArcMethod_StartCentertLength(ShDrawArcAction *drawArcAction, ShGraphicView *view);
	~ShDrawArcMethod_StartCentertLength();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);

private:
	bool GetArcDataWithStartCenterLength(const ShPoint3d& start, const ShPoint3d& center, double length,
		ShArcData &arcData);

};

////////////////////////////////////////////////////////////////////////////////////////////


class ShDrawArcMethod_StartEndAngle : public ShDrawArcMethod {

private:
	ShPoint3d start;
	ShPoint3d end;

public:
	ShDrawArcMethod_StartEndAngle(ShDrawArcAction *drawArcAction, ShGraphicView *view);
	~ShDrawArcMethod_StartEndAngle();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);

private:
	bool GetArcDataWithStartEndAnother(const ShPoint3d& start, const ShPoint3d& end, const ShPoint3d& another,
		ShArcData& data);
};


class ShDrawArcMethod_StartEndDirection : public ShDrawArcMethod {

public:
	ShDrawArcMethod_StartEndDirection(ShDrawArcAction *drawArcAction, ShGraphicView *view);
	~ShDrawArcMethod_StartEndDirection();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);

};


class ShDrawArcMethod_StartEndRadius : public ShDrawArcMethod {

private:
	ShPoint3d start;
	ShPoint3d end;

public:
	ShDrawArcMethod_StartEndRadius(ShDrawArcAction *drawArcAction, ShGraphicView *view);
	~ShDrawArcMethod_StartEndRadius();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);

private:
	bool GetArcDataWithStartEndAnother(const ShPoint3d& start, const ShPoint3d& end, const ShPoint3d& another,
		ShArcData& data);
};

/////////////////////////////////////////////////////////////////////////////////////////////

class ShDrawArcMethod_CenterStartEnd : public ShDrawArcMethod {

public:
	ShDrawArcMethod_CenterStartEnd(ShDrawArcAction *drawArcAction, ShGraphicView *view);
	~ShDrawArcMethod_CenterStartEnd();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);

};


class ShDrawArcMethod_CenterStartAngle : public ShDrawArcMethod {

private:
	ShPoint3d center;
	ShPoint3d start;

public:
	ShDrawArcMethod_CenterStartAngle(ShDrawArcAction *drawArcAction, ShGraphicView *view);
	~ShDrawArcMethod_CenterStartAngle();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);

};


class ShDrawArcMethod_CenterStartLength : public ShDrawArcMethod {

private:
	ShPoint3d center;
	ShPoint3d start;

public:
	ShDrawArcMethod_CenterStartLength(ShDrawArcAction *drawArcAction, ShGraphicView *view);
	~ShDrawArcMethod_CenterStartLength();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);

	bool GetArcDataWithCenterStartLength(const ShPoint3d& center, const ShPoint3d& start, double length,
		ShArcData &arcData);
};


#endif //_SHDRAWARCACTION_H