

#ifndef _SHDIMACTION_H
#define _SHDIMACTION_H

#include "ActionHandler\DrawAction\ShDrawAction.h"

class ShDimAction : public ShDrawAction {

public:
	ShDimAction(ShCADWidget *widget);
	virtual ~ShDimAction() = 0;


};

#endif //_SHDIMACTION_H