

#ifndef _SHDRAFTDATA_H
#define _SHDRAFTDATA_H

#include "Base\ShVariable.h"
class ShObjectSnapData;

class ShDraftData {

private:
	bool orthModeOn;
	ObjectSnap disposableSnap;
	ShObjectSnapData* objectSnapData;
	

public:
	ShDraftData();
	~ShDraftData();

	void setOrthMode(bool on);
	void setDisposableSnap(ObjectSnap objectSnap);

	
	inline bool getOrthMode() const { return this->orthModeOn; }
	inline ObjectSnap getDisposableSnap() const { return this->disposableSnap; }

};

#endif //_SHDRAFTDATA_H