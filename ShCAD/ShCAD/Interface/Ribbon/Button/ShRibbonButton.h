

#ifndef _SHRIBBONBUTTON_H
#define _SHRIBBONBUTTON_H

#include "Interface\Item\ShButton.h"

class ShRibbonButtonStrategy;
class ShAbstractRibbonButton : public ShButtonWithMenuPopupWithText {
	Q_OBJECT
protected:
	ShRibbonButtonStrategy *strategy;

public:
	ShAbstractRibbonButton(QWidget *parent = nullptr);
	virtual ~ShAbstractRibbonButton() = 0;

protected:
	void changeStrategy(ShRibbonButtonStrategy *strategy);

	private slots:
	void buttonClicked();

};


class ShRibbonCircleButton : public ShAbstractRibbonButton {
	Q_OBJECT

public:
	ShRibbonCircleButton(QWidget *parent = nullptr);
	~ShRibbonCircleButton();

	private slots:
	void centerRadiusActionClicked();
	void centerDiameterActionClicked();
	void twoPointActionClicked();
	void threePointActionClicked();


};

class ShRibbonArcButton : public ShAbstractRibbonButton {

	Q_OBJECT

public:
	ShRibbonArcButton(QWidget *parent = nullptr);
	~ShRibbonArcButton();

	private slots:
	void threePointActionClicked();

	void startCenterEndActionClicked();
	void startCenterAngleActionClicked();
	void startCenterLengthActionClicked();

	void startEndAngleActionClicked();
	void startEndDirectionActionClicked();
	void startEndRadiusActionClicked();

	void centerStartEndActionClicked();
	void centerStartAngleActionClicked();
	void centerStartLengthActionClicked();

};

class ShRibbonPolyLineButton : public ShAbstractRibbonButton {

	Q_OBJECT

public:
	ShRibbonPolyLineButton(QWidget *parent = nullptr);
	~ShRibbonPolyLineButton();

	private slots:
	void polyLineActionClicked();
	void rectangleActionClicked();
	void polygonActionClicked();

};


#endif //_SHRIBBONBUTTON_H