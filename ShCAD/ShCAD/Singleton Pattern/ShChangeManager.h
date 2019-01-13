

#ifndef _SHCHANGEMANAGER_H
#define _SHCHANGEMANAGER_H

// Mediator pattern / Singleton Pattern / Observer Pattern
#include "ShVariable.h"

class ShStatusBar;
class ShGraphicView;
class ShChangeManager {

private:
	ShChangeManager();
	~ShChangeManager();

	static ShChangeManager instance;

public:
	static ShChangeManager* GetInstance();

	void Register(ShStatusBar *statusBar);

	void Notify(ShGraphicView *view, NotifyEvent event);
	

private:
	ShStatusBar *statusBar;

};

#endif //_SHCHANGEMANAGER_H