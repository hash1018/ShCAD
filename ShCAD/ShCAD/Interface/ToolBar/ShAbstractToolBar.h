

#ifndef _SHABSTRACTTOOLBAR_H
#define _SHABSTRACTTOOLBAR_H

#include <qtoolbar.h>
class ShCAD;
class ShAbstractToolBar : public QToolBar {

protected:
	bool menuActionChecked;
	QAction *menuAction;
	
public:
	ShAbstractToolBar(const QString& title, QWidget *parent = 0);
	virtual ~ShAbstractToolBar() = 0;

	inline QAction* GetMenuAction() const { return this->menuAction; }
	inline bool MenuActionChecked() const { return this->menuActionChecked; }

	void Activate();
	void DeActivate();

	private slots:
	void MenuActionClicked();

protected:
	void GetIcon(const QString& filePath, QIcon& icon);
};

#endif //_SHABSTRACTTOOLBAR_H