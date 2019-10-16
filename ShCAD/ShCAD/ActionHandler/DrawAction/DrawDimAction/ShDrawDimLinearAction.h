

#ifndef _SHDRAWDIMLINEARACTION_H
#define _SHDRAWDIMLINEARACTION_H

#include "ShDrawDimAction.h"

class ShDimLinearData;

class ShDrawDimLinearAction : public ShDrawDimAction {

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
	ShDrawDimLinearAction(ShCADWidget *widget);
	~ShDrawDimLinearAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);

protected:
	virtual void trigger(const ShPoint3d &point);

private:
	void getDimLinearData(const ShPoint3d &first, const ShPoint3d &second, const ShPoint3d &point, 
		Direction &direction, ShDimLinearData &data);
};

#endif //_SHDRAWDIMLINEARACTION_H