

#ifndef _SHDIMLINEARACTION_H
#define _SHDIMLINEARACTION_H

#include "ShDimAction.h"

class ShDimLinearData;

class ShDimLinearAction : public ShDimAction {

public:
	enum Status {

		PickedNothing,
		PickedFirst,
		PickedSecond,
	};

	enum Direction {

		Nothing,
		Vertical,
		Horizontal,
	};

private:
	Status status;
	ShPoint3d first;
	ShPoint3d second;
	Direction direction;
	
public:
	ShDimLinearAction(ShCADWidget *widget);
	~ShDimLinearAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);

protected:
	virtual void trigger(const ShPoint3d &point);
};

#endif //_SHDIMLINEARACTION_H