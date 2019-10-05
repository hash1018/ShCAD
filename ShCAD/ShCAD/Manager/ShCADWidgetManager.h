
#ifndef _SHCADWIDGETMANAGER_H
#define _SHCADWIDGETMANAGER_H

#include "Base\ShSingleton.h"
#include <qlist.h>

class ShCADWidget;
class ShCADWidgetManager {

	DeclarSingleton(ShCADWidgetManager)

private:
	QList<ShCADWidget*> list;
	int nameIndex;

private:
	ShCADWidget *activatedWidget;

public:
	ShCADWidget* getActivatedWidget();

	void add(ShCADWidget *widget);
	void remove(ShCADWidget *widget);

	void setActivatedWidget(ShCADWidget *widget);

};

#endif //_SHCADWIDGETMANAGER_H