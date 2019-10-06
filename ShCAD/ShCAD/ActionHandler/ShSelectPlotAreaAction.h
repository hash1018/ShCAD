
#ifndef _SHSELECTPLOTAREAACTION_H
#define _SHSELECTPLOTAREAACTION_H

#include "ShActionHandler.h"

class ShPlotDialog;

class ShSelectPlotAreaAction : public ShActionHandler {

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
	ShSelectPlotAreaAction(ShCADWidget *widget);
	~ShSelectPlotAreaAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();
	virtual QCursor getCursorShape();
	virtual void draw(QPainter *painter);
	virtual void invalidate(ShPoint3d &point);

	void setPlotDialog(ShPlotDialog *plotDialog) { this->plotDialog = plotDialog; }

protected:
	virtual void trigger(const ShPoint3d &point);
};

#endif //_SHSELECTPLOTAREAACTION_H