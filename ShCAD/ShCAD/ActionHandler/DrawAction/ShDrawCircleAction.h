
#ifndef _SHDRAWCIRCLEACTION_H
#define _SHDRAWCIRCLEACTION_H

#include "ShDrawAction.h"

class ShDrawCircleAction : public ShDrawAction {

	friend class ShSubDrawCircleAction;

public:
	enum Status {
		PickedNothing,
		PickedCenter,
		PickedFirstPoint,
		PickedSecondPoint,
	
	};

	enum SubAction {
		CenterRadius,
		CenterDiameter,
		TwoPoint,
		ThreePoint,

	};

private:
	Status status;
	SubAction subAction;
	ShSubDrawCircleAction *subDrawCircleAction;

public:
	ShDrawCircleAction(ShCADWidget *widget, SubAction subAction = SubAction::CenterRadius);
	~ShDrawCircleAction();

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


class ShSubDrawCircleAction {

protected:
	ShDrawCircleAction *drawCircleAction;
	ShCADWidget *widget;

public:
	ShSubDrawCircleAction(ShDrawCircleAction *drawCircleAction, ShCADWidget *widget);
	virtual ~ShSubDrawCircleAction() = 0;

	void mouseLeftPressEvent(ShActionData &data);
	void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType() = 0;
	virtual QString getHeadTitle() = 0;
	virtual ShAvailableDraft getAvailableDraft() = 0;

	virtual void invalidate(ShPoint3d &point) = 0;
	virtual ShPoint3d getLastPickedPoint() = 0;
	virtual void trigger(const ShPoint3d &point) = 0;

protected:
	ShDrawCircleAction::Status& getStatus();
	void addEntity(ShEntity *newEntity, const QString &type);
	void triggerSucceeded();
	void actionFinished();
};


///////////////////////////////////////////////////////////////////////////////


class ShSubDrawCircleAction_CenterRadius : public ShSubDrawCircleAction {

public:
	ShSubDrawCircleAction_CenterRadius(ShDrawCircleAction *drawCircleAction, ShCADWidget *widget);
	~ShSubDrawCircleAction_CenterRadius();

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);
	virtual ShPoint3d getLastPickedPoint();
	virtual void trigger(const ShPoint3d &point);

};


//////////////////////////////////////////////////////////////////////////////////

class ShSubDrawCircleAction_CenterDiameter : public ShSubDrawCircleAction {

public:
	ShSubDrawCircleAction_CenterDiameter(ShDrawCircleAction *drawCircleAction, ShCADWidget *widget);
	~ShSubDrawCircleAction_CenterDiameter();

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);
	virtual ShPoint3d getLastPickedPoint();
	virtual void trigger(const ShPoint3d &point);

};


////////////////////////////////////////////////////////////////////////////////


class ShSubDrawCircleAction_TwoPoint : public ShSubDrawCircleAction {

public:
	ShSubDrawCircleAction_TwoPoint(ShDrawCircleAction *drawCircleAction, ShCADWidget *widget);
	~ShSubDrawCircleAction_TwoPoint();

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);
	virtual ShPoint3d getLastPickedPoint();
	virtual void trigger(const ShPoint3d &point);

private:
	ShPoint3d getCenter(const ShPoint3d &first, const ShPoint3d &second);
};



///////////////////////////////////////////////////////////////////////////////

class ShSubDrawCircleAction_ThreePoint : public ShSubDrawCircleAction {

private:
	ShPoint3d first;
	ShPoint3d second;

public:
	ShSubDrawCircleAction_ThreePoint(ShDrawCircleAction *drawCircleAction, ShCADWidget *widget);
	~ShSubDrawCircleAction_ThreePoint();

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);
	virtual ShPoint3d getLastPickedPoint();
	virtual void trigger(const ShPoint3d &point);

};


#endif //_SHDRAWCIRCLEACTION_H