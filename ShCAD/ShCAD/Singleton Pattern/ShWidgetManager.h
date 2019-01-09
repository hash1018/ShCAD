

#ifndef _SHWIDGETMANAGER_H
#define _SHWIDGETMANAGER_H

class ShCADWidget;
class ShWidgetManager {

	
private:
	ShCADWidget *activatedWidget;

	//Single pattern
private:
	ShWidgetManager();
	~ShWidgetManager();

	static ShWidgetManager instance;

public:
	static ShWidgetManager* GetInstance();
	static ShCADWidget* GetActivatedWidget();

	void SetActivatedWidget(ShCADWidget *activated);
};

#endif //_SHWIDGETMANAGER_H