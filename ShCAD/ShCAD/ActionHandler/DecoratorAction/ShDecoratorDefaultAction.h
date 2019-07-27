
#ifndef _SHDECORATORDEFAULTACTION_H
#define _SHDECORATORDEFAULTACTION_H

#include "ShDecoratorAction.h"

class ShDecoratorDefaultAction : public ShDecoratorAction {

public:
	ShDecoratorDefaultAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	~ShDecoratorDefaultAction();

};

#endif //_SHDECORATORDEFAULTACTION_H