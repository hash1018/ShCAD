

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
	ShCAD *shCAD;
	QMenu *toolBarMenu;

	QList<ShAbstractToolBar*> list;

private:

	ShDrawToolBar *drawToolBar;
	ShPropertyToolBar *propertyToolBar;
	ShModifyToolBar *modifyToolBar;
	ShLayerToolBar *layerToolBar;
	ShObjectSnapToolBar *objectSnapToolBar;

public:
	ShToolBarContainer(ShCAD *shCAD);
	~ShToolBarContainer();

	void Activate();
	void DeActivate();

	inline QMenu* GetToolBarMenu() const { return this->toolBarMenu; }

private:
	void CreateToolBars();
};



#endif //_SHTOOLBARCONTAINER_H