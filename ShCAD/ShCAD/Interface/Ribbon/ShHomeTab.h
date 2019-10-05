

#ifndef _SHHOMETAB_H
#define _SHHOMETAB_H

#include "ShRibbon.h"
#include "Event\ShObserver.h"

class ShNotifyEvent;
class ShDrawPanel;
class ShModifyPanel;
class ShPropertyPanel;
class ShLayerPanel;
class ShButton;
class ShRibbonCircleButton;
class ShRibbonArcButton;
class ShRibbonPolyLineButton;
class ShButtonWithText;
class ShColor;
class ShColorComboBox;
class ShLineStyle;
class ShLineStyleComboBox;
class ShLayerComboBox;
class ShLayer;
class ShAnnotatePanel;
class ShRibbonDimensionButton;

class ShHomeTab : public ShRibbonTab {

	Q_OBJECT
private:
	ShDrawPanel *drawPanel;
	ShModifyPanel *modifyPanel;
	ShPropertyPanel *propertyPanel;
	ShLayerPanel *layerPanel;
	ShAnnotatePanel *annotatePanel;

public:
	ShHomeTab(ShChain *chain, const QString &title, QWidget *parent = nullptr);
	~ShHomeTab();

	void update(ShNotifyEvent *event);
};


class ShDrawPanel : public ShPanelInRibbonTab {
	Q_OBJECT

private:
	ShButtonWithText *lineButton;
	ShRibbonCircleButton *circleButton;
	ShRibbonArcButton *arcButton;
	ShRibbonPolyLineButton *polyButton;

public:
	ShDrawPanel(ShChain *chain, QWidget *parent, const QString &title, int width);
	~ShDrawPanel();

protected:
	void resizeEvent(QResizeEvent *event);

	private slots:
	void lineButtonClicked();

};

////////////////////////////////////////////////////////////////////

class ShModifyPanel : public ShPanelInRibbonTab {
	Q_OBJECT

private:
	ShButtonWithText *moveButton;
	ShButtonWithText *copyButton;
	ShButtonWithText *stretchButton;

	ShButtonWithText *rotateButton;
	ShButtonWithText *mirrorButton;
	ShButtonWithText *scaleButton;

	ShButtonWithText *eraseButton;
	ShButtonWithText *extendButton;
	ShButtonWithText *trimButton;

public:
	ShModifyPanel(ShChain *chain, QWidget *parent, const QString &title, int width);
	~ShModifyPanel();

protected:
	void resizeEvent(QResizeEvent *event);

	private slots:
	void moveButtonClicked();
	void copyButtonClicked();
	void stretchButtonClicked();
	void rotateButtonClicked();
	void mirrorButtonClicked();
	void scaleButtonClicked();
	void eraseButtonClicked();
	void extendButtonClicked();
	void trimButtonClicked();

};


////////////////////////////////////////////////////////////////////

class ShAnnotatePanel : public ShPanelInRibbonTab {
	Q_OBJECT

private:
	ShRibbonDimensionButton *dimensionButton;

public:
	ShAnnotatePanel(ShChain *chain, QWidget *parent, const QString &title, int width);
	~ShAnnotatePanel();

protected:
	void resizeEvent(QResizeEvent *event);


};


////////////////////////////////////////////////////////////////////

class ShPropertyPanel : public ShPanelInRibbonTab {
	Q_OBJECT

private:
	ShButton *colorButton;
	ShColorComboBox *colorCombo;
	ShLineStyleComboBox *lineStyleCombo;

public:
	ShPropertyPanel(ShChain *chain, QWidget *parent, const QString &title, int width);
	~ShPropertyPanel();

	void update(ShNotifyEvent *event);

	inline ShColorComboBox* getColorCombo() const { return this->colorCombo; }
	inline ShLineStyleComboBox* getLineStyleCombo() const { return this->lineStyleCombo; }
	inline ShButton* getColorButton() const { return this->colorButton; }

protected:
	void resizeEvent(QResizeEvent* event);

	private slots:
	void colorButtonClicked();
	void colorChanged(const ShColor &color);
	void lineStyleChanged(const ShLineStyle &lineStyle);
};

//////////////////////////////////////////////////////////////////////////////

class ShLayerPanel : public ShPanelInRibbonTab {
	Q_OBJECT

private:
	ShLayerComboBox *layerCombo;

public:
	ShLayerPanel(ShChain *chain, QWidget *parent, const QString &title, int width);
	~ShLayerPanel();

	void update(ShNotifyEvent *event);

	inline ShLayerComboBox* getLayerCombo() const { return this->layerCombo; }

protected:
	void resizeEvent(QResizeEvent *event);

	private slots:
	void currentLayerChanged(ShLayer *layer);
	void layerTurnChanged(ShLayer *layer, bool turnOn);
	void layerColorChanged(ShLayer *layer, const ShColor &color);
};

#endif //_SHHOMETAB_H