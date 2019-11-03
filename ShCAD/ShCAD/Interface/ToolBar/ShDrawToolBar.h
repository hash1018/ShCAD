
#ifndef _SHDRAWTOOLBAR_H
#define _SHDRAWTOOLBAR_H

#include "ShAbstractToolBar.h"

class ShDrawToolBar : public ShAbstractToolBar {

public:
	ShDrawToolBar(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShDrawToolBar();

private:

	private slots :
	void lineActionClicked();
	void constructionLineActionClicked();
	void polyLineActionClicked();
	void circleActionClicked();
	void arcActionClicked();
	void pointActionClicked();
};

#endif //_SHDRAWTOOLBAR_H