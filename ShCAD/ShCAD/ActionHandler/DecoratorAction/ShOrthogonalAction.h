
#ifndef _SHORTHOGONALACTION_H
#define _SHORTHOGONALACTION_H

#include "ShDecoratorAction.h"

class ShOrthogonalAction : public ShDecoratorAction {

public:
	ShOrthogonalAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	~ShOrthogonalAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void invalidate(ShDecoratorActionData &data);

protected:
	void getOrthogonalPoint(double x, double y, double mouseX, double mouseY, double &orthX, double &orthY);
};

#endif //_SHORTHOGONALACTION_H
