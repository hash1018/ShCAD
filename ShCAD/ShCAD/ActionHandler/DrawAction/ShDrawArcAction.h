

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



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////





class ShSubDrawArcAction_StartCenterEnd : public ShSubDrawArcAction {

private:
	ShPoint3d start;
	ShPoint3d center;

public:
	ShSubDrawArcAction_StartCenterEnd(ShDrawArcAction *drawArcAction, ShCADWidget *widget);
	~ShSubDrawArcAction_StartCenterEnd();

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);
	virtual ShPoint3d getLastPickedPoint();
	virtual void trigger(const ShPoint3d &point);

};


////////////////////////////////////////////////////////////////////////////

class ShSubDrawArcAction_StartCenterAngle : public ShSubDrawArcAction {

private:
	ShPoint3d start;
	ShPoint3d center;

public:
	ShSubDrawArcAction_StartCenterAngle(ShDrawArcAction *drawArcAction, ShCADWidget *widget);
	~ShSubDrawArcAction_StartCenterAngle();

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);
	virtual ShPoint3d getLastPickedPoint();
	virtual void trigger(const ShPoint3d &point);

};

/////////////////////////////////////////////////////////////////////////////


class ShSubDrawArcAction_StartCenterLength : public ShSubDrawArcAction {

private:
	ShPoint3d start;
	ShPoint3d center;

public:
	ShSubDrawArcAction_StartCenterLength(ShDrawArcAction *drawArcAction, ShCADWidget *widget);
	~ShSubDrawArcAction_StartCenterLength();

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);
	virtual ShPoint3d getLastPickedPoint();
	virtual void trigger(const ShPoint3d &point);

private:
	bool getArcDataWithStartCenterLength(const ShPoint3d &start, const ShPoint3d &center, double length, ShArcData &data);
};


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

class ShSubDrawArcAction_StartEndAngle : public ShSubDrawArcAction {

private:
	ShPoint3d start;
	ShPoint3d end;

public:
	ShSubDrawArcAction_StartEndAngle(ShDrawArcAction *drawArcAction, ShCADWidget *widget);
	~ShSubDrawArcAction_StartEndAngle();

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);
	virtual ShPoint3d getLastPickedPoint();
	virtual void trigger(const ShPoint3d &point);

private:
	bool getArcDataWithStartEndAnother(const ShPoint3d &start, const ShPoint3d &end, const ShPoint3d &another, ShArcData &data);
};


//////////////////////////////////////////////////////////////////////////////////

class ShSubDrawArcAction_StartEndDirection : public ShSubDrawArcAction {

private:
	ShPoint3d start;
	ShPoint3d end;

public:
	ShSubDrawArcAction_StartEndDirection(ShDrawArcAction *drawArcAction, ShCADWidget *widget);
	~ShSubDrawArcAction_StartEndDirection();

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);
	virtual ShPoint3d getLastPickedPoint();
	virtual void trigger(const ShPoint3d &point);

private:
	ShArcData getArcDataWithTwoPointTangentLine(const ShPoint3d &first, const ShPoint3d &second, const ShPoint3d &lineStart, const ShPoint3d &lineEnd);
};


/////////////////////////////////////////////////////////////////////////////////////

class ShSubDrawArcAction_StartEndRadius : public ShSubDrawArcAction {

private:
	ShPoint3d start;
	ShPoint3d end;

public:
	ShSubDrawArcAction_StartEndRadius(ShDrawArcAction *drawArcAction, ShCADWidget *widget);
	~ShSubDrawArcAction_StartEndRadius();

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);
	virtual ShPoint3d getLastPickedPoint();
	virtual void trigger(const ShPoint3d &point);

private:
	bool getArcDataWithStartEndAnother(const ShPoint3d &start, const ShPoint3d &end, const ShPoint3d &another, ShArcData &data);
};

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

class ShSubDrawArcAction_CenterStartEnd : public ShSubDrawArcAction {

private:
	ShPoint3d center;
	ShPoint3d start;

public:
	ShSubDrawArcAction_CenterStartEnd(ShDrawArcAction *drawArcAction, ShCADWidget *widget);
	~ShSubDrawArcAction_CenterStartEnd();

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);
	virtual ShPoint3d getLastPickedPoint();
	virtual void trigger(const ShPoint3d &point);

};

//////////////////////////////////////////////////////////////////////////////////////////


class ShSubDrawArcAction_CenterStartAngle : public ShSubDrawArcAction {

private:
	ShPoint3d center;
	ShPoint3d start;

public:
	ShSubDrawArcAction_CenterStartAngle(ShDrawArcAction *drawArcAction, ShCADWidget *widget);
	~ShSubDrawArcAction_CenterStartAngle();

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);
	virtual ShPoint3d getLastPickedPoint();
	virtual void trigger(const ShPoint3d &point);

};


/////////////////////////////////////////////////////////////////////////////////////////

class ShSubDrawArcAction_CenterStartLength : public ShSubDrawArcAction {

private:
	ShPoint3d center;
	ShPoint3d start;

public:
	ShSubDrawArcAction_CenterStartLength(ShDrawArcAction *drawArcAction, ShCADWidget *widget);
	~ShSubDrawArcAction_CenterStartLength();

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);
	virtual ShPoint3d getLastPickedPoint();
	virtual void trigger(const ShPoint3d &point);

private:
	bool getArcDataWithCenterStartLength(const ShPoint3d &center, const ShPoint3d &start, double length, ShArcData &data);
};

#endif //_SHDRAWARCACTION_H