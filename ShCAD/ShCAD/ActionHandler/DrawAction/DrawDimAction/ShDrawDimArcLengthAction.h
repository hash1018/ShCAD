

#ifndef _SHDRAWDIMARCLENGTHACTION_H
#define _SHDRAWDIMARCLENGTHACTION_H

#include "ShDrawDimAction.h"

class ShDimArcLengthData;

class ShDrawDimArcLengthAction : public ShDrawDimAction {

public:
	enum Status {
		PickedNothing,
		PickedShape,

	};

private:
	Status status;
	ShPoint3d center;
	ShPoint3d start;
	ShPoint3d end;
	double radius;
	

public:
	ShDrawDimArcLengthAction(ShCADWidget *widget);
	~ShDrawDimArcLengthAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();
	virtual QCursor getCursorShape();

	virtual void invalidate(ShPoint3d &point);

protected:
	virtual void trigger(const ShPoint3d &point);

private:
	void getDimArcLengthData(const ShPoint3d &center, double radius, const ShPoint3d &start, const ShPoint3d &end, const ShPoint3d &point, ShDimArcLengthData &data);

};

#endif //_SHDRAWDIMARCLENGTHACTION_H