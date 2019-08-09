
#ifndef _SHCHANGEMANAGER_H
#define _SHCHANGEMANAGER_H

// Mediator Pattern, Singleton Pattern, Observer Pattern.

class ShNotifyEvent;
class ShCADWidget;
class ShStatusBar;
class ShCommandDock;
class ShRibbonMenu;
class ShToolBarContainer;

class ShChangeManager {

private:
	ShChangeManager();
	~ShChangeManager();

	static ShChangeManager instance;

public:
	static ShChangeManager* getInstance();

public:
	void registerObserver(ShStatusBar *statusBar);
	void registerObserver(ShCommandDock *commandDock);
	void registerObserver(ShRibbonMenu *ribbonMenu);
	void registerObserver(ShToolBarContainer *toolBarContainer);


	void notify(ShCADWidget *widget, ShNotifyEvent *event);
	

private:
	ShStatusBar *statusBar;
	ShCommandDock *commandDock;
	ShRibbonMenu *ribbonMenu;
	ShToolBarContainer *toolBarContainer;
};

#endif //_SHCHANGEMANAGER_H