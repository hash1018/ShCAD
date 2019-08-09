

#ifndef _SHPROPERTYTOOLBAR_H
#define _SHPROPERTYTOOLBAR_H

#include "ShAbstractToolBar.h"

class ShNotifyEvent;
class ShColorComboBox;
class ShColor;

class ShPropertyToolBar : public ShAbstractToolBar {
	Q_OBJECT

private:
	ShColorComboBox *colorCombo;


public:
	ShPropertyToolBar(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShPropertyToolBar();

	void update(ShNotifyEvent *event);

	private slots:
	void colorChanged(const ShColor &color);
};


#endif //_SHPROPERTYTOOLBAR_H