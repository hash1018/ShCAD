

#ifndef _SHRIBBONBUTTON_H
#define _SHRIBBONBUTTON_H

#include "Interface\Items\ShCustomizedWidget.h"

class ShButtonWithMenuPopupStrategy;
class ShAbstractRibbonButton : public ShButtonWithMenuPopup {

protected:
	ShButtonWithMenuPopupStrategy *strategy;

public:
	ShAbstractRibbonButton(QWidget *parent = 0);
	virtual ~ShAbstractRibbonButton() = 0;

protected:
	void ChangeStrategy(ShButtonWithMenuPopupStrategy *strategy);

private:
	void ButtonClicked();
};

class ShRibbonCircleButton : public ShAbstractRibbonButton {
	Q_OBJECT

	
public:
	ShRibbonCircleButton(QWidget *parent = 0);
	~ShRibbonCircleButton();


	private slots:
	void CenterRadiusActionClicked();
	void CenterDiameterActionClicked();
	void TwoPointActionClicked();
	void ThreePointActionClicked();
};


class ShRibbonArcButton : public ShAbstractRibbonButton {
	Q_OBJECT

public:
	ShRibbonArcButton(QWidget *parent = 0);
	~ShRibbonArcButton();
		
	private slots:
	void ThreePointActionClicked();

	void StartCenterEndActionClicked();
	void StartCenterAngleActionClicked();
	void StartCenterLengthActionClicked();

	void StartEndAngleActionClicked();
	void StartEndDirectionActionClicked();
	void StartEndRadiusActionClicked();

	void CenterStartEndActionClicked();
	void CenterStartAngleActionClicked();
	void CenterStartLengthActionClicked();

};

class ShRibbonPolyLineButton : public ShAbstractRibbonButton {
	Q_OBJECT

public:
	ShRibbonPolyLineButton(QWidget *parent = 0);
	~ShRibbonPolyLineButton();
	
	private slots:
	void PolyLineActionClicked();
	void RectangleActionClicked();
	void PolygonActionClicked();

};

#endif //_SHRIBBONBUTTON_H