

#ifndef _SHWIDGETMANAGER_H
#define _SHWIDGETMANAGER_H

#include <qlist.h>

class ShGraphicView;
class ShWidgetManager {

	
private:
	QList<ShGraphicView*> list;
	int nameIndex;


private:
	ShGraphicView *activatedWidget;

	//Single pattern
private:
	ShWidgetManager();
	~ShWidgetManager();

	static ShWidgetManager instance;

public:
	static ShWidgetManager* GetInstance();
	ShGraphicView* GetActivatedWidget();

	void Add(ShGraphicView *view);
	void Remove(ShGraphicView *view);

	void SetActivatedWidget(ShGraphicView *activated);
};

#endif //_SHWIDGETMANAGER_H