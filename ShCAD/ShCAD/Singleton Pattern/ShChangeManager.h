

#ifndef _SHCHANGEMANAGER_H
#define _SHCHANGEMANAGER_H

// Mediator pattern / Singleton Pattern / Observer Pattern

class ShNotifyEvent;
class ShStatusBar;
class ShGraphicView;
class ShCommandDock;
class ShChangeManager {

private:
	ShChangeManager();
	~ShChangeManager();

	static ShChangeManager instance;

public:
	static ShChangeManager* GetInstance();

	void Register(ShStatusBar *statusBar);
	void Register(ShCommandDock *commandDock);

	void Notify(ShGraphicView *view, ShNotifyEvent *event);
	void Notify(ShCommandDock* commandDock, ShNotifyEvent *event);
	

private:
	ShStatusBar *statusBar;
	ShCommandDock *commandDock;

};

#endif //_SHCHANGEMANAGER_H