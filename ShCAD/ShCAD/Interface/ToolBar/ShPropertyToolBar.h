

#ifndef _SHPROPERTYTOOLBAR_H
#define _SHPROPERTYTOOLBAR_H

#include "ShAbstractToolBar.h"

class ShNotifyEvent;
class ShColorComboBox;
class ShColor;
class ShLineStyleComboBox;
class ShLineStyle;

class ShPropertyToolBar : public ShAbstractToolBar {
	Q_OBJECT

private:
	ShColorComboBox *colorCombo;
	ShLineStyleComboBox *lineStyleCombo;


public:
	ShPropertyToolBar(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShPropertyToolBar();

	void update(ShNotifyEvent *event);

	inline ShColorComboBox* getColorCombo() const { return this->colorCombo; }
	inline ShLineStyleComboBox* getLineStyleCombo() const { return this->lineStyleCombo; }

	private slots:
	void colorChanged(const ShColor &color);
	void lineStyleChanged(const ShLineStyle &lineStyle);
};


#endif //_SHPROPERTYTOOLBAR_H