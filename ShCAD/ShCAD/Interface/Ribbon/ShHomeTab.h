

#ifndef _SHHOMETAB_H
#define _SHHOMETAB_H

#include "ShRibbon.h"

class ShDrawColumn;
class ShModifyColumn;
class ShPropertyColumn;
class ShLayerColumn;
class ShHomeTab : public ShRibbonTab {
	Q_OBJECT
private:
	ShDrawColumn *drawColumn;
	ShModifyColumn *modifyColumn;
	ShPropertyColumn *propertyColumn;
	ShLayerColumn *layerColumn;

public:
	ShHomeTab(const QString &title, QWidget *parent = 0);
	~ShHomeTab();

};

///////////////////////////////////////////////////////////////////

class ShButtonWithMenuPopup;
class ShRibbonCircleButton;
class ShRibbonArcButton;
class ShDrawColumn : public ShColumnInRibbonTab {
	Q_OBJECT
private:
	ShButtonWithMenuPopup *lineButton;
	ShRibbonCircleButton *circleButton;
	ShRibbonArcButton *arcButton;
public:
	ShDrawColumn(QWidget *parent, const QString &title, int width);
	~ShDrawColumn();

protected:
	void resizeEvent(QResizeEvent *event);

	private slots:
	void LineButtonClicked();
	

private:
	void InitLineButton();
	
};

////////////////////////////////////////////////////////////////////
class ShButton;
class ShModifyColumn : public ShColumnInRibbonTab {
	Q_OBJECT
private:
	ShButton *moveButton;
	ShButton *copyButton;
	ShButton *stretchButton;

	ShButton *rotateButton;
	ShButton *mirrorButton;
	ShButton *scaleButton;

	ShButton *eraseButton;
	ShButton *extendButton;
	ShButton *trimButton;

public:
	ShModifyColumn(QWidget *parent, const QString &title, int width);
	~ShModifyColumn();

protected:
	void resizeEvent(QResizeEvent *event);

	private slots:
	void MoveButtonClicked();
	void CopyButtonClicked();
	void StretchButtonClicked();
	void RotateButtonClicked();
	void MirrorButtonClicked();
	void ScaleButtonClicked();
	void EraseButtonClicked();
	void ExtendButtonClicked();
	void TrimButtonClicked();

};


////////////////////////////////////////////////////////////////////

class ShColorComboBox;
class ShActivatedWidgetChangedEvent;
class ShCurrentLayerChangedEvent;
class ShLayerComboSelChangedEvent;
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
	//QPushButton *colorCustomButton;
	ShButton *colorCustomButton;
	ShColorComboBox *colorCombo;

	ShLineStyleComboBox *lineStyleCombo;

public:
	ShPropertyColumn(QWidget *parent, const QString &title, int width);
	~ShPropertyColumn();

	void Update(ShActivatedWidgetChangedEvent *event);
	void Update(ShCurrentLayerChangedEvent *event);
	void Update(ShLayerComboSelChangedEvent *event);
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
	void Update(ShSelectedEntityCountChangedEvent *event);
	void Notify(ShNotifyEvent *event);
	void SynchronizeLayerCombo();
	void SynchronizeLayerCombo(int index);
	int GetCurrentComboIndex();

protected:
	void resizeEvent(QResizeEvent *event);

	private slots:
	void CurrentIndexChanged(int index);
	void LayerTurnChanged(ShLayer*, bool previous);
	void LayerColorChanged(ShLayer*, const ShColor& previous);
};

#endif //_SHHOMETAB_H