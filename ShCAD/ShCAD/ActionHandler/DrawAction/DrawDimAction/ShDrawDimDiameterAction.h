
#ifndef _SHDRAWDIMDIAMETERACTION_H
#define _SHDRAWDIMDIAMETERACTION_H

#include "ShDrawDimAction.h"

class ShDimDiameterData;

class ShDrawDimDiameterAction : public ShDrawDimAction {

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
	ShDrawDimDiameterAction(ShCADWidget *widget);
	~ShDrawDimDiameterAction();

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
	void getDimDiameterData(const ShPoint3d &center, double radius, const ShPoint3d &point, ShDimDiameterData &data);

};

#endif //_SHDRAWDIMDIAMETERACTION_H