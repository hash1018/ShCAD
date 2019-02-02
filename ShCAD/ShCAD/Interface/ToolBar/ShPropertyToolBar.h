

#ifndef _SHPROPERTYTOOLBAR_H
#define _SHPROPERTYTOOLBAR_H

#include <qtoolbar.h>

class ShColorComboBox;
class ShActivatedWidgetChangedEvent;
class ShCurrentLayerChangedEvent;
class ShLayerDataChangedEvent;
class ShCurrentActionChangedEvent;
class ShSelectedEntityCountChangedEvent;
class ShNotifyEvent;
class ShColor;
class ShLineStyleComboBox;
class ShLineStyle;


class ShPropertyToolBar : public QToolBar {
	Q_OBJECT

private:
	ShColorComboBox *colorCombo;
	ShLineStyleComboBox *lineStyleCombo;
	 
	

public:
	ShPropertyToolBar(QWidget *parent = 0);
	~ShPropertyToolBar();

	void Update(ShActivatedWidgetChangedEvent *event);
	void Update(ShCurrentLayerChangedEvent *event);
	void Update(ShLayerDataChangedEvent *event);
	void Update(ShCurrentActionChangedEvent *event);
	void Update(ShSelectedEntityCountChangedEvent *event);


	void Notify(ShNotifyEvent *event);
	void SynchronizeColorCombo(int colorComboIndex);
	void SynchronizeColorCombo(const ShColor& color);
	int GetColorComboIndex();

	void SynchronizeLineStyleCombo(int lineStyleComboIndex);
	void SynchronizeLineStyleCombo(const ShLineStyle& lineStyle);
	int GetLineStyleComboIndex();


private:
 
	void SetColorComboInfo(const ShColor& blockColor, const ShColor& layerColor, const ShColor& current);
	void SetLineStyleComboInfo(const ShLineStyle& blockLineStyle, const ShLineStyle& layerLineStyle, const ShLineStyle& current);


	private slots:
	void ColorSelChanged(const ShColor& color);
	void LineStyleSelChanged(const ShLineStyle& lineStyle);
	
};


#endif //_SHPROPERTYTOOLBAR_H