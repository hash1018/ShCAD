

#ifndef _SHWIDGETMANAGER_H
#define _SHWIDGETMANAGER_H

class ShGraphicView;
class ShWidgetManager {

	
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

	void SetActivatedWidget(ShGraphicView *activated);
};

#endif //_SHWIDGETMANAGER_H