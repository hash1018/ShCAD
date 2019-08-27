

#ifndef _SHDRAWARCACTION_H
#define _SHDRAWARCACTION_H

#include "ShDrawAction.h"

class ShDrawArcAction : public ShDrawAction {

	friend class ShSubDrawArcAction;

public:
	enum Status {
		PickedNothing,
		PickedCenter,
		PickedFirstPoint,
		PickedSecondPoint,
		PickedStart,
		PickedEnd,

	};

	enum SubAction {
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
	SubAction subAction;
	ShSubDrawArcAction *subDrawArcAction;

public:
	ShDrawArcAction(ShCADWidget *widget, SubAction subAction = SubAction::ThreePoint);
	~ShDrawArcAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);

	virtual ShPoint3d getLastPickedPoint();

protected:
	virtual void trigger(const ShPoint3d &point);

private:
	void changeSubAction(SubAction subAction);

};


////////////////////////////////////////////////////////////////////////////


class ShSubDrawArcAction {

protected:
	ShDrawArcAction *drawArcAction;
	ShCADWidget *widget;

public:
	ShSubDrawArcAction(ShDrawArcAction *drawArcAction, ShCADWidget *widget);
	virtual ~ShSubDrawArcAction() = 0;

	void mouseLeftPressEvent(ShActionData &data);
	void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType() = 0;
	virtual QString getHeadTitle() = 0;
	virtual ShAvailableDraft getAvailableDraft() = 0;

	virtual void invalidate(ShPoint3d &point) = 0;
	virtual ShPoint3d getLastPickedPoint() = 0;
	virtual void trigger(const ShPoint3d &point) = 0;

protected:
	ShDrawArcAction::Status& getStatus();
	void addEntity(ShEntity *newEntity, const QString &type);
	void triggerSucceeded();
	void actionFinished();
};


///////////////////////////////////////////////////////////////////////



class ShSubDrawArcAction_ThreePoint : public ShSubDrawArcAction {

private:
	ShPoint3d first;
	ShPoint3d second;

public:
	ShSubDrawArcAction_ThreePoint(ShDrawArcAction *drawArcAction, ShCADWidget *widget);
	~ShSubDrawArcAction_ThreePoint();

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);
	virtual ShPoint3d getLastPickedPoint();
	virtual void trigger(const ShPoint3d &point);

private:
	bool getArcDataWithThreePoint(const ShPoint3d &first, const ShPoint3d &second, const ShPoint3d &third, ShArcData &data);
};

#endif //_SHDRAWARCACTION_H