
#ifndef _SHCADWIDGETMANAGER_H
#define _SHCADWIDGETMANAGER_H


//Singleton Pattern

#include <qlist.h>

class ShCADWidget;
class ShCADWidgetManager {

private:
	QList<ShCADWidget*> list;
	int nameIndex;

private:
	ShCADWidget *activatedWidget;

private:
	ShCADWidgetManager();
	~ShCADWidgetManager();

	static ShCADWidgetManager instance;

public:
	static ShCADWidgetManager* getInstance();
	ShCADWidget* getActivatedWidget();

	void add(ShCADWidget *widget);
	void remove(ShCADWidget *widget);

	void setActivatedWidget(ShCADWidget *widget);

};

#endif //_SHCADWIDGETMANAGER_H