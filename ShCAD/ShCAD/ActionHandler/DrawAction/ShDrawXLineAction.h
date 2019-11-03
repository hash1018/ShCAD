
#ifndef _SHDRAWXLINEACTION_H
#define _SHDRAWXLINEACTION_H

#include "ShDrawAction.h"

class ShLineData;

class ShDrawXLineAction : public ShDrawAction {

public:
	enum Status {
		PickedNothing,
		PickedMid,
	};

private:
	Status status;

public:
	ShDrawXLineAction(ShCADWidget *widget);
	~ShDrawXLineAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);

protected:
	virtual void trigger(const ShPoint3d &point);

private:
	void getData(const ShPoint3d &mid, const ShPoint3d &point, ShLineData &data);


};

#endif //_SHDRAWXLINEACTION_H