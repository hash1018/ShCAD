

#ifndef _SHHOMETAB_H
#define _SHHOMETAB_H

#include "ShRibbon.h"

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

class ShHomeTab : public ShRibbonTab {

	Q_OBJECT
private:
	ShDrawPanel *drawPanel;
	ShModifyPanel *modifyPanel;
	ShPropertyPanel *propertyPanel;
	ShLayerPanel *layerPanel;

public:
	ShHomeTab(ShChain *chain, const QString &title, QWidget *parent = nullptr);
	~ShHomeTab();

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


class ShPropertyPanel : public ShPanelInRibbonTab {
	Q_OBJECT

private:
	ShColorComboBox *colorCombo;

public:
	ShPropertyPanel(ShChain *chain, QWidget *parent, const QString &title, int width);
	~ShPropertyPanel();

protected:
	void resizeEvent(QResizeEvent* event);

	private slots:
	void colorChanged(const ShColor &color);
};

//////////////////////////////////////////////////////////////////////////////

class ShLayerPanel : public ShPanelInRibbonTab {
	Q_OBJECT


public:
	ShLayerPanel(ShChain *chain, QWidget *parent, const QString &title, int width);
	~ShLayerPanel();


protected:
	void resizeEvent(QResizeEvent *event);

};

#endif //_SHHOMETAB_H