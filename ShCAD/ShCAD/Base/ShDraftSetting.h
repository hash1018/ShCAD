
#ifndef _SHDRAFTSETTING_H
#define _SHDRAFTSETTING_H

#include "Data\ShObjectSnapData.h"

class ShDraftSetting {

private:
	ShObjectSnapData objectSnapData;


private:
	ShDraftSetting();
	~ShDraftSetting();

	static ShDraftSetting instance;

public:
	static ShDraftSetting* getInstance();

	ShObjectSnapData* getObjectSnapData() { return &(this->objectSnapData); }


};

#endif //_SHDRAFTSETTING_H