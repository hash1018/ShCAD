

#ifndef _SHPROPERTYTOOLBAR_H
#define _SHPROPERTYTOOLBAR_H

#include <qtoolbar.h>

class ShColorComboBox;
class ShActivatedWidgetChangedEvent;
class ShNotifyEvent;
class ShColor;
class ShLineStyleComboBox;
class ShLineStyle;

class ShLayerComboBox; //only temporary.
class ShPropertyToolBar : public QToolBar {
	Q_OBJECT

private:
	ShColorComboBox *colorCombo;
	ShLineStyleComboBox *lineStyleCombo;
	 
	ShLayerComboBox *layerCombo; //only temporary.

public:
	ShPropertyToolBar(QWidget *parent = 0);
	~ShPropertyToolBar();

	void Update(ShActivatedWidgetChangedEvent *event);
	void Notify(ShNotifyEvent *event);
	void SynchronizeColorCombo(int colorComboIndex);
	int GetColorComboIndex();

	void SynchronizeLineStyleCombo(int lineStyleComboIndex);
	int GetLineStyleComboIndex();


private:
 
	private slots:
	void ColorSelChanged(const ShColor& color);
	void LineStyleSelChanged(const ShLineStyle& lineStyle);
	
};


#endif //_SHPROPERTYTOOLBAR_H