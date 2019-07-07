
#ifndef _SHCHANGEMANAGER_H
#define _SHCHANGEMANAGER_H

// Mediator Pattern, Singleton Pattern, Observer Pattern.

class ShNotifyEvent;
class ShCADWidget;
class ShStatusBar;
class ShCommandDock;

class ShChangeManager {

private:
	ShChangeManager();
	~ShChangeManager();

	static ShChangeManager instance;

public:
	static ShChangeManager* getInstance();

public:
	void Register(ShStatusBar *statusBar);
	void Register(ShCommandDock *commandDock);


	void notify(ShCADWidget *widget, ShNotifyEvent *event);

private:
	ShStatusBar *statusBar;
	ShCommandDock *commandDock;
};

#endif //_SHCHANGEMANAGER_H