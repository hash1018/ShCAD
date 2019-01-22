

#ifndef _SHCHANGEMANAGER_H
#define _SHCHANGEMANAGER_H

// Mediator pattern / Singleton Pattern / Observer Pattern

class ShNotifyEvent;
class ShStatusBar;
class ShGraphicView;
class ShCommandDock;
class ShPropertyColumn;
class ShChangeManager {

private:
	ShChangeManager();
	~ShChangeManager();

	static ShChangeManager instance;

public:
	static ShChangeManager* GetInstance();

	void Register(ShStatusBar *statusBar);
	void Register(ShCommandDock *commandDock);
	void Register(ShPropertyColumn *propertyColumn); // this function is called in constructor of ShPropertyColumn.

	void Notify(ShGraphicView *view, ShNotifyEvent *event);
	void Notify(ShCommandDock* commandDock, ShNotifyEvent *event);
	void Notify(ShPropertyColumn *propertyColumn, ShNotifyEvent *event);
	

private:
	ShStatusBar *statusBar;
	ShCommandDock *commandDock;
	ShPropertyColumn *propertyColumn;

};

#endif //_SHCHANGEMANAGER_H