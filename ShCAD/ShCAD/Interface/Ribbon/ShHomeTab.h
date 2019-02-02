

#ifndef _SHHOMETAB_H
#define _SHHOMETAB_H

#include "ShRibbon.h"
#include "Interface\Items\ShCustomizedWidget.h"

class ShDrawColumn;
class ShPropertyColumn;
class ShLayerColumn;
class ShHomeTab : public ShRibbonTab {
	Q_OBJECT
private:
	ShDrawColumn *drawColumn;
	ShPropertyColumn *propertyColumn;
	ShLayerColumn *layerColumn;

public:
	ShHomeTab(const QString &title, QWidget *parent = 0);
	~ShHomeTab();

};

///////////////////////////////////////////////////////////////////

class ShDrawColumn : public ShColumnInRibbonTab {
	Q_OBJECT
private:
	ShButtonWithMenuPopup *lineButton;
	ShButtonWithMenuPopup *circleButton;
	ShButtonWithMenuPopup *arcButton;
public:
	ShDrawColumn(QWidget *parent, const QString &title, int width);
	~ShDrawColumn();

protected:
	void resizeEvent(QResizeEvent *event);

	private slots:
	void LineButtonClicked();
	void CircleButtonClicked();
	void ArcButtonClicked();

private:
	void InitLineButton();
	void InitCircleButton();
	void InitArcButton();
};


////////////////////////////////////////////////////////////////////

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
class ShPropertyColumn : public ShColumnInRibbonTab {
	Q_OBJECT

private:
	QPushButton *colorCustomButton;
	ShColorComboBox *colorCombo;

	ShLineStyleComboBox *lineStyleCombo;

public:
	ShPropertyColumn(QWidget *parent, const QString &title, int width);
	~ShPropertyColumn();

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


	
protected:
	void resizeEvent(QResizeEvent* event);

private:
	void SetColorComboInfo(const ShColor& blockColor, const ShColor& layerColor, const ShColor& current);
	void SetLineStyleComboInfo(const ShLineStyle& blockLineStyle, const ShLineStyle& layerLineStyle, const ShLineStyle& current);


	private slots:
	void ColorCustomButtonClicked();
	void ColorSelChanged(const ShColor& color);
	void LineStyleSelChanged(const ShLineStyle& lineStyle);
	
};

//////////////////////////////////////////////////////////////////////////////

class ShLayerComboBox;
class ShLayer;
class ShColor;
class ShLayerColumn : public ShColumnInRibbonTab {
	Q_OBJECT

private:
	ShLayerComboBox *layerCombo;

public:
	ShLayerColumn(QWidget *parent, const QString &title, int width);
	~ShLayerColumn();

	void Update(ShActivatedWidgetChangedEvent *event);
	void Update(ShCurrentActionChangedEvent *event);
	void Notify(ShNotifyEvent *event);
	void SynchronizeLayerCombo();

protected:
	void resizeEvent(QResizeEvent *event);

	private slots:
	void CurrentLayerChanged(ShLayer *previousLayer, ShLayer *currentLayer);
	void LayerTurnChanged(ShLayer*, bool previous);
	void LayerColorChanged(ShLayer*, const ShColor& previous);
};

#endif //_SHHOMETAB_H