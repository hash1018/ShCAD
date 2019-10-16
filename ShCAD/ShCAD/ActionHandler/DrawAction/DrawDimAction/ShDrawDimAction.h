

#ifndef _SHDRAWDIMACTION_H
#define _SHDRAWDIMACTION_H

#include "ActionHandler\DrawAction\ShDrawAction.h"

class ShDrawDimAction : public ShDrawAction {

public:
	ShDrawDimAction(ShCADWidget *widget);
	virtual ~ShDrawDimAction() = 0;


};

#endif //_SHDRAWDIMACTION_H