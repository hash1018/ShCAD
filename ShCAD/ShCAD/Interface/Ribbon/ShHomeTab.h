

#ifndef _SHHOMETAB_H
#define _SHHOMETAB_H

#include "ShRibbon.h"
#include "Interface\Items\ShCustomizedWidget.h"

class ShDrawColumn;
class ShPropertyColumn;
class ShHomeTab : public ShRibbonTab {
	Q_OBJECT
private:
	ShDrawColumn *drawColumn;
	ShPropertyColumn *propertyColumn;
	
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
class ShNotifyEvent;
class ShColor;
class ShPropertyColumn : public ShColumnInRibbonTab {
	Q_OBJECT

private:
	QPushButton *colorCustomButton;
	ShColorComboBox *colorCombo;

public:
	ShPropertyColumn(QWidget *parent, const QString &title, int width);
	~ShPropertyColumn();

	void Update(ShActivatedWidgetChangedEvent *event);
	void Notify(ShNotifyEvent *event);
	void SynchronizeColorCombo(int colorComboIndex);
	int GetColorComboIndex();


	
protected:
	void resizeEvent(QResizeEvent* event);


	private slots:
	void ColorCustomButtonClicked();
	void ColorSelChanged(const ShColor& color);
	
};


#endif //_SHHOMETAB_H