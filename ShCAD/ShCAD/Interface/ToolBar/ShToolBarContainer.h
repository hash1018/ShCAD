

#ifndef _SHTOOLBARCONTAINER_H
#define _SHTOOLBARCONTAINER_H

#include <qlist.h>
#include "Chain of Responsibility\ShChain.h"

class ShNotifyEvent;
class ShCAD;
class QMenu;
class ShDrawToolBar;
class ShPropertyToolBar;
class ShModifyToolBar;
class ShLayerToolBar;
class ShObjectSnapToolBar;
class ShAbstractToolBar;
class ShToolBarContainer : public ShChain {

private:
	ShCAD *parent;
	QMenu *toolBarMenu;

	QList<ShAbstractToolBar*> list;

private:

	ShDrawToolBar *drawToolBar;
	ShPropertyToolBar *propertyToolBar;
	ShModifyToolBar *modifyToolBar;
	ShLayerToolBar *layerToolBar;
	ShObjectSnapToolBar *objectSnapToolBar;

public:
	ShToolBarContainer(ShCAD *parent, ShChain *chain);
	~ShToolBarContainer();

	void activate();
	void deactivate();

	void update(ShNotifyEvent *event);

	inline QMenu* getToolBarMenu() const { return this->toolBarMenu; }

	void readSettings();
	void writeSettings();

private:
	void createToolBars();
};



#endif //_SHTOOLBARCONTAINER_H