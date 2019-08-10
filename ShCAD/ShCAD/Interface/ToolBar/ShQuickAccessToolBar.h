
#ifndef _SHQUICKACCESSTOOLBAR_H
#define _SHQUICKACCESSTOOLBAR_H

#include "ShAbstractToolBar.h"

class ShQuickAccessToolBar : public ShAbstractToolBar {

public:
	ShQuickAccessToolBar(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShQuickAccessToolBar();



	private slots :
	void newActionClicked();
	

};

#endif //_SHQUICKACCESSTOOLBAR_H