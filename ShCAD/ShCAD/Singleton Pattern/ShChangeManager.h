

#ifndef _SHCHANGEMANAGER_H
#define _SHCHANGEMANAGER_H

// Mediator pattern / Singleton Pattern / Observer Pattern

class ShNotifyEvent;
class ShStatusBar;
class ShGraphicView;
class ShCommandDock;
class ShPropertyColumn;
class ShPropertyToolBar;
class ShLayerToolBar;
class ShLayerColumn;
class ShLayerDialog;
class ShChangeCurrentLayerCommand;
class ShChangeLayerDataCommand;
class ShCreateLayerCommand;
class ShDeleteLayerCommand;
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
	void Register(ShPropertyToolBar *propertyToolBar); //this function is called in constructor of ShPropertyToolBar.
	void Register(ShLayerToolBar *layerToolBar); //this function is called in constructor of ShLayerToolBar.
	void Register(ShLayerColumn *layerColumn);  //this function is called in constructor of ShLayerColumn.


	void Notify(ShGraphicView *view, ShNotifyEvent *event);
	void Notify(ShCommandDock* commandDock, ShNotifyEvent *event);
	void Notify(ShPropertyColumn *propertyColumn, ShNotifyEvent *event);
	void Notify(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event);
	void Notify(ShLayerToolBar *layerToolBar, ShNotifyEvent *event);
	void Notify(ShLayerColumn *layerColumn, ShNotifyEvent *event);
	void Notify(ShLayerDialog *layerDialog, ShNotifyEvent *event);
	void Notify(ShChangeCurrentLayerCommand *changeCurrentLayerCommand, ShNotifyEvent *event);
	void Notfiy(ShChangeLayerDataCommand *changeLayerDataCommand, ShNotifyEvent *event);
	void Notify(ShCreateLayerCommand *createLayerCommand, ShNotifyEvent *event);
	void Notify(ShDeleteLayerCommand *deleteLayerCommand, ShNotifyEvent *event);


private:
	ShStatusBar *statusBar;
	ShCommandDock *commandDock;
	ShPropertyColumn *propertyColumn;
	ShPropertyToolBar *propertyToolBar;
	ShLayerToolBar *layerToolBar;
	ShLayerColumn *layerColumn;

};

#endif //_SHCHANGEMANAGER_H