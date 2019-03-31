
#ifndef _SHDRAWTOOLBAR_H
#define _SHDRAWTOOLBAR_H

#include "ShAbstractToolBar.h"
class ShDrawToolBar : public ShAbstractToolBar {

public:
	ShDrawToolBar(const QString &title, QWidget *parent = 0);
	~ShDrawToolBar();

private:
	

	private slots:
	void LineActionClicked();
	void PolyLineActionClicked();
	void CircleActionClicked();
	void ArcActionClicked();
};

#endif //_SHDRAWTOOLBAR_H