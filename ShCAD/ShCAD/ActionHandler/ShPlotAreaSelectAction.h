
#ifndef _SHPLOTAREASELECTACTION_H
#define _SHPLOTAREASELECTACTION_H

#include "ShActionHandler.h"

class ShPlotDialog;
class ShPlotAreaSelectAction : public ShActionHandler {

public:
	enum Status {
		PickedNothing,
		PickedFirstPoint,
	};

private:
	Status status;
	ShPlotDialog *plotDialog;

	double firstX;
	double firstY;
	double secondX;
	double secondY;
	

public:
	ShPlotAreaSelectAction(ShGraphicView *graphicView);
	~ShPlotAreaSelectAction();

	virtual void LMousePressEvent(QMouseEvent *event, ShActionData& data);

	virtual void MouseMoveEvent(QMouseEvent *event, ShActionData& data);
	virtual void KeyPressEvent(QKeyEvent *event, ShActionData& data);

	virtual ActionType GetType();

	void SetPlotDialog(ShPlotDialog *plotDialog) { this->plotDialog = plotDialog; }

	virtual QCursor GetCursorShape();
	virtual void Draw(QPainter *painter);

	virtual QString GetActionHeadTitle();
};

#endif //_SHPLOTAREASELECTACTION_H