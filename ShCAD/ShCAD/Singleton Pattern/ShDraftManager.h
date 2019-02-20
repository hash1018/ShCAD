

#ifndef _SHDRAFTMANAGER_H
#define _SHDRAFTMANAGER_H

class ShDraftManager {

private:
	ShDraftManager();
	~ShDraftManager();

	static ShDraftManager instance;

public:
	static ShDraftManager* GetInstance();

};

#endif //_SHDRAFTMANAGER_H