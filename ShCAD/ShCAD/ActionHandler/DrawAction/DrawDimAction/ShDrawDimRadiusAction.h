
#ifndef _SHDRAWDIMRADIUSACTION_H
#define _SHDRAWDIMRADIUSACTION_H

#include "ShDrawDimAction.h"

class ShDimRadiusData;

class ShDrawDimRadiusAction : public ShDrawDimAction {

public:
	enum Status {
		PickedNothing,
		PickedShape,

	};

private:
	Status status;
	ShPoint3d center;
	double radius;

public:
	ShDrawDimRadiusAction(ShCADWidget *widget);
	~ShDrawDimRadiusAction();

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
	void getDimRadiusData(const ShPoint3d &center, double radius, const ShPoint3d &point, ShDimRadiusData &data);

};

#endif //_SHDRAWDIMRADIUSACTION_H