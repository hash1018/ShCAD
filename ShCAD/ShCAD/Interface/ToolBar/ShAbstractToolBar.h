
#ifndef _SHABSTRACTTOOLBAR_H
#define _SHABSTRACTTOOLBAR_H

#include <qtoolbar.h>
#include "Chain of Responsibility\ShChain.h"

class ShAbstractToolBar : public QToolBar , public ShChain {

protected:
	bool menuActionChecked;
	QAction *menuAction;

public:
	ShAbstractToolBar(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	virtual ~ShAbstractToolBar() = 0;

	inline QAction* GetMenuAction() const { return this->menuAction; }
	inline bool isMenuActionChecked() const { return this->menuActionChecked; }

	void activate();
	void deactivate();

	private slots:
	void menuActionClicked();


};

#endif //_SHABSTRACTTOOLBAR_H