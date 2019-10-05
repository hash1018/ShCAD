
#ifndef _SHDRAFTSETTING_H
#define _SHDRAFTSETTING_H

#include "Data\ShObjectSnapData.h"
#include "Base\ShSingleton.h"

class ShDraftSetting {

	DeclareSingleton(ShDraftSetting)

private:
	ShObjectSnapData objectSnapData;

public:
	ShObjectSnapData* getObjectSnapData() { return &(this->objectSnapData); }

};

#endif //_SHDRAFTSETTING_H