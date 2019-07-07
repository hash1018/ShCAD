
#ifndef _SHABSTRACTTOOLBAR_H
#define _SHABSTRACTTOOLBAR_H

#include <qtoolbar.h>

class ShAbstractToolBar : public QToolBar {

protected:
	bool menuActionChecked;
	QAction *menuAction;

public:
	ShAbstractToolBar(const QString &title, QWidget *parent = nullptr);
	virtual ~ShAbstractToolBar() = 0;

	inline QAction* GetMenuAction() const { return this->menuAction; }
	inline bool isMenuActionChecked() const { return this->menuActionChecked; }

	void activate();
	void deactivate();

	private slots:
	void menuActionClicked();


};

#endif //_SHABSTRACTTOOLBAR_H