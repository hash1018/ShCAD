

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


class ShHomeTab : public ShRibbonTab {

	Q_OBJECT
private:
	ShDrawPanel *drawPanel;
	ShModifyPanel *modifyPanel;
	ShPropertyPanel *propertyPanel;
	ShLayerPanel *layerPanel;

public:
	ShHomeTab(const QString &title, QWidget *parent = nullptr);
	~ShHomeTab();

};


class ShDrawPanel : public ShPanelInRibbonTab {
	Q_OBJECT

private:
	ShRibbonCircleButton *circleButton;
	ShRibbonArcButton *arcButton;
	ShRibbonPolyLineButton *polyButton;

public:
	ShDrawPanel(QWidget *parent, const QString &title, int width);
	~ShDrawPanel();

protected:
	void resizeEvent(QResizeEvent *event);

};

////////////////////////////////////////////////////////////////////

class ShModifyPanel : public ShPanelInRibbonTab {
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
	ShModifyPanel(QWidget *parent, const QString &title, int width);
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


public:
	ShPropertyPanel(QWidget *parent, const QString &title, int width);
	~ShPropertyPanel();

protected:
	void resizeEvent(QResizeEvent* event);

};

//////////////////////////////////////////////////////////////////////////////

class ShLayerPanel : public ShPanelInRibbonTab {
	Q_OBJECT


public:
	ShLayerPanel(QWidget *parent, const QString &title, int width);
	~ShLayerPanel();


protected:
	void resizeEvent(QResizeEvent *event);

};

#endif //_SHHOMETAB_H