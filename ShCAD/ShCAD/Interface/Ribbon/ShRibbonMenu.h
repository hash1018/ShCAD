
#ifndef _SHRIBBONMENU_H
#define _SHRIBBONMENU_H

#include "ShRibbon.h"

class ShHomeTab;
class ShInsertTab;
class ShAnnotateTab;
class ShParametricTab;
class ShViewTab;
class ShManageTab;
class ShRibbonMenu : public ShRibbon {

private:
	ShHomeTab *homeTab;
	ShInsertTab *insertTab;
	ShAnnotateTab *annotateTab;
	ShParametricTab *parametricTab;
	ShViewTab *viewTab;
	ShManageTab *manageTab;

	bool menuActionChecked;
	QAction *menuAction;

public:
	ShRibbonMenu(int height, QWidget *parent = nullptr);
	~ShRibbonMenu();

	inline QAction* getMenuAction() const { return this->menuAction; }
	inline bool isMenuActionChecked() const { return this->menuActionChecked; }

	void activate();
	void deactivate();

	private slots:
	void menuActionClicked();

};



class ShInsertTab : public ShRibbonTab {

public:
	ShInsertTab(const QString &title, QWidget *parent = nullptr);
	~ShInsertTab();

};

class ShAnnotateTab : public ShRibbonTab {

public:
	ShAnnotateTab(const QString &title, QWidget *parent = nullptr);
	~ShAnnotateTab();

};

class ShParametricTab : public ShRibbonTab {

public:
	ShParametricTab(const QString &title, QWidget *parent = nullptr);
	~ShParametricTab();

};

class ShViewTab : public ShRibbonTab {

public:
	ShViewTab(const QString &title, QWidget *parent = nullptr);
	~ShViewTab();

};

class ShManageTab : public ShRibbonTab {

public:
	ShManageTab(const QString &title, QWidget *parent = nullptr);
	~ShManageTab();

};

#endif //_SHRIBBONMENU_H