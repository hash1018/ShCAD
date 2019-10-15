


#ifndef _SHDIMALIGNEDACTION_H
#define _SHDIMALIGNEDACTION_H

#include "ShDimAction.h"

class ShDimAlignedData;

class ShDimAlignedAction : public ShDimAction {

public:
	enum Status {

		PickedNothing,
		PickedFirst,
		PickedSecond,
	};

private:
	Status status;
	ShPoint3d first;
	ShPoint3d second;
	

public:
	ShDimAlignedAction(ShCADWidget *widget);
	~ShDimAlignedAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);

protected:
	virtual void trigger(const ShPoint3d &point);

private:
	void getDimAlignedData(const ShPoint3d &first, const ShPoint3d &second, const ShPoint3d &point, ShDimAlignedData &data);
};

#endif //_SHDIMALIGNEDACTION_H

