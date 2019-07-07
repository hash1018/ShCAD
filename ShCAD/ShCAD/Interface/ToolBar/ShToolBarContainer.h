

#ifndef _SHTOOLBARCONTAINER_H
#define _SHTOOLBARCONTAINER_H

#include <qlist.h>

class ShCAD;
class QMenu;
class ShDrawToolBar;
class ShPropertyToolBar;
class ShModifyToolBar;
class ShLayerToolBar;
class ShObjectSnapToolBar;
class ShAbstractToolBar;
class ShToolBarContainer {

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
	ShToolBarContainer(ShCAD *parent);
	~ShToolBarContainer();

	void activate();
	void deactivate();

	inline QMenu* getToolBarMenu() const { return this->toolBarMenu; }

private:
	void createToolBars();
};



#endif //_SHTOOLBARCONTAINER_H