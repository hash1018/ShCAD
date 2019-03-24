
#ifndef _SHDRAWPOLYLINEACTION_H
#define _SHDRAWPOLYLINEACTION_H

#include "ShDrawAction.h"
class ShPolyLine;
class ShDrawPolyLineAction : public ShDrawAction {

public:
	enum Status {
		PickedNothing,
		PickedStart,
	};

private:
	Status status;
	Status previous;
	ShPolyLine *polyLine;

public:
	ShDrawPolyLineAction(ShGraphicView *graphicView);
	~ShDrawPolyLineAction();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);
	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data);

	virtual ActionType GetType();

	virtual void ApplyOrthogonalShape(bool on);
	virtual QString GetActionHeadTitle();
	virtual void IsAllowedDraftOperation(ShAllowedDraftData &data);


};

#endif //_SHDRAWPOLYLINEACTION_H