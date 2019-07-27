

#ifndef _DRAFTDATA_H
#define _DRAFTDATA_H

#include "Base\ShVariable.h"
class ShObjectSnapData;

class DraftData {

private:
	bool orthModeOn;
	ObjectSnap disposableSnap;
	ShObjectSnapData* objectSnapData;
	

public:
	DraftData();
	~DraftData();

	void setOrthMode(bool on);
	void setDisposableSnap(ObjectSnap objectSnap);

	
	inline bool getOrthMode() const { return this->orthModeOn; }

};

#endif //_DRAFTDATA_H