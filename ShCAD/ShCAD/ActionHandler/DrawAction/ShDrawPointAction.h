
#ifndef _SHDRAWPOINTACTION_H
#define _SHDRAWPOINTACTION_H

#include "ShDrawAction.h"

class ShDrawPointAction : public ShDrawAction {

public:
	ShDrawPointAction(ShCADWidget *widget);
	~ShDrawPointAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual ShAvailableDraft getAvailableDraft();

	virtual void invalidate(ShPoint3d &point);

protected:
	virtual void trigger(const ShPoint3d &point);

};

#endif //_SHDRAWPOINTACTION_H