
#include "ShRibbonButton.h"
#include <qmenu.h>
#include "Interface\Private\ShRibbonButtonStrategy.h"
#include "Manager\ShLanguageManager.h"

ShAbstractRibbonButton::ShAbstractRibbonButton(QWidget *parent)
	:ShButtonWithMenuPopupWithText(parent), strategy(0) {

	connect(this, &ShButtonWithMenuPopupWithText::pressed, this, &ShAbstractRibbonButton::buttonClicked);
}

ShAbstractRibbonButton::~ShAbstractRibbonButton() {

	if (this->strategy != 0)
		delete this->strategy;
}

void ShAbstractRibbonButton::buttonClicked() {

	if (this->strategy != 0)
		this->strategy->execute();

}

void ShAbstractRibbonButton::changeStrategy(ShRibbonButtonStrategy *strategy) {

	if (this->strategy != 0)
		delete this->strategy;

	this->strategy = strategy;
	this->setIcon(this->strategy->getIcon());
	this->setToolTip(this->strategy->getToolTip());

}

///////////////////////////////////////////////////////////////////////////////////

ShRibbonCircleButton::ShRibbonCircleButton(QWidget *parent)
	:ShAbstractRibbonButton(parent) {

	this->setTextDirection(South);
	this->setText(shGetLanValue_ui("Draw/Circle"));
	this->setIconSize(this->size());

	this->strategy = new ShRibbonCircleButtonCenterRadiusStrategy;
	this->setIcon(this->strategy->getIcon());
	this->setToolTip(this->strategy->getToolTip());

	QMenu *menu = new QMenu(this->popupButton);
	menu->addAction(ShRibbonCircleButtonCenterRadiusStrategy::getIcon_(), "Center, Radius", this, SLOT(centerRadiusActionClicked()));
	menu->addAction(ShRibbonCircleButtonCenterDiameterStrategy::getIcon_(), "Center, Diameter", this, SLOT(centerDiameterActionClicked()));
	menu->addSeparator();
	menu->addAction(ShRibbonCircleButtonTwoPointStrategy::getIcon_(), "2-Point", this, SLOT(twoPointActionClicked()));
	menu->addAction(ShRibbonCircleButtonThreePointStrategy::getIcon_(), "3-Point", this, SLOT(threePointActionClicked()));

	this->popupButton->setMenu(menu);



}

ShRibbonCircleButton::~ShRibbonCircleButton() {

}

void ShRibbonCircleButton::centerRadiusActionClicked() {
	this->changeStrategy(new ShRibbonCircleButtonCenterRadiusStrategy);
	this->strategy->execute();
}

void ShRibbonCircleButton::centerDiameterActionClicked() {
	this->changeStrategy(new ShRibbonCircleButtonCenterDiameterStrategy);
	this->strategy->execute();
}

void ShRibbonCircleButton::twoPointActionClicked() {
	this->changeStrategy(new ShRibbonCircleButtonTwoPointStrategy);
	this->strategy->execute();
}

void ShRibbonCircleButton::threePointActionClicked() {
	this->changeStrategy(new ShRibbonCircleButtonThreePointStrategy);
	this->strategy->execute();
}

//////////////////////////////////////////////////////////////////////////////////////

ShRibbonArcButton::ShRibbonArcButton(QWidget *parent)
	:ShAbstractRibbonButton(parent) {

	this->setTextDirection(South);
	this->setText(shGetLanValue_ui("Draw/Arc"));
	this->setIconSize(this->size());

	this->strategy = new ShRibbonArcButtonThreePointStrategy;
	this->setIcon(this->strategy->getIcon());
	this->setToolTip(this->strategy->getToolTip());

	QMenu *menu = new QMenu(this->popupButton);
	menu->addAction(ShRibbonArcButtonThreePointStrategy::getIcon_(), "3-Point",
		this, SLOT(threePointActionClicked()));

	menu->addSeparator();

	menu->addAction(ShRibbonArcButtonStartCenterEndStrategy::getIcon_(), "Start, Center, End",
		this, SLOT(startCenterEndActionClicked()));

	menu->addAction(ShRibbonArcButtonStartCenterAngleStrategy::getIcon_(), "Start, Center, Angle",
		this, SLOT(startCenterAngleActionClicked()));

	menu->addAction(ShRibbonArcButtonStartCenterLengthStrategy::getIcon_(), "Start, Center, Length",
		this, SLOT(startCenterLengthActionClicked()));

	menu->addSeparator();

	menu->addAction(ShRibbonArcButtonStartEndAngleStrategy::getIcon_(), "Start, End, Angle",
		this, SLOT(startEndAngleActionClicked()));

	menu->addAction(ShRibbonArcButtonStartEndDirectionStrategy::getIcon_(), "Start, End, Direction",
		this, SLOT(startEndDirectionActionClicked()));

	menu->addAction(ShRibbonArcButtonStartEndRadiusStrategy::getIcon_(), "Start, End, Radius",
		this, SLOT(startEndRadiusActionClicked()));

	menu->addSeparator();

	menu->addAction(ShRibbonArcButtonCenterStartEndStrategy::getIcon_(), "Center, Start, End",
		this, SLOT(centerStartEndActionClicked()));

	menu->addAction(ShRibbonArcButtonCenterStartAngleStrategy::getIcon_(), "Center, Start, Angle",
		this, SLOT(centerStartAngleActionClicked()));

	menu->addAction(ShRibbonArcButtonCenterStartLengthStrategy::getIcon_(), "Center, Start, Length",
		this, SLOT(centerStartLengthActionClicked()));

	this->popupButton->setMenu(menu);
}

ShRibbonArcButton::~ShRibbonArcButton() {


}

void ShRibbonArcButton::threePointActionClicked() {
	this->changeStrategy(new ShRibbonArcButtonThreePointStrategy);
	this->strategy->execute();
}

void ShRibbonArcButton::startCenterEndActionClicked() {
	this->changeStrategy(new ShRibbonArcButtonStartCenterEndStrategy);
	this->strategy->execute();
}

void ShRibbonArcButton::startCenterAngleActionClicked() {
	this->changeStrategy(new ShRibbonArcButtonStartCenterAngleStrategy);
	this->strategy->execute();
}

void ShRibbonArcButton::startCenterLengthActionClicked() {
	this->changeStrategy(new ShRibbonArcButtonStartCenterLengthStrategy);
	this->strategy->execute();
}

void ShRibbonArcButton::startEndAngleActionClicked() {
	this->changeStrategy(new ShRibbonArcButtonStartEndAngleStrategy);
	this->strategy->execute();
}

void ShRibbonArcButton::startEndDirectionActionClicked() {
	this->changeStrategy(new ShRibbonArcButtonStartEndDirectionStrategy);
	this->strategy->execute();
}

void ShRibbonArcButton::startEndRadiusActionClicked() {
	this->changeStrategy(new ShRibbonArcButtonStartEndRadiusStrategy);
	this->strategy->execute();
}

void ShRibbonArcButton::centerStartEndActionClicked() {
	this->changeStrategy(new ShRibbonArcButtonCenterStartEndStrategy);
	this->strategy->execute();
}

void ShRibbonArcButton::centerStartAngleActionClicked() {
	this->changeStrategy(new ShRibbonArcButtonCenterStartAngleStrategy);
	this->strategy->execute();
}

void ShRibbonArcButton::centerStartLengthActionClicked() {
	this->changeStrategy(new ShRibbonArcButtonCenterStartLengthStrategy);
	this->strategy->execute();
}

/////////////////////////////////////////////////////////////////////////////

ShRibbonPolyLineButton::ShRibbonPolyLineButton(QWidget *parent)
	:ShAbstractRibbonButton(parent) {

	this->setTextDirection(South);
	this->setText(shGetLanValue_ui("Draw/PolyLine"));
	this->setIconSize(this->size());

	this->strategy = new ShRibbonPolyLineButtonStrategy;
	this->setIcon(this->strategy->getIcon());
	this->setToolTip(this->strategy->getToolTip());

	QMenu *menu = new QMenu(this->popupButton);
	menu->addAction(ShRibbonPolyLineButtonStrategy::getIcon_(), "PolyLine",
		this, SLOT(polyLineActionClicked()));
	menu->addAction(ShRibbonRectangleButtonStrategy::getIcon_(), "Rectangle",
		this, SLOT(rectangleActionClicked()));
	menu->addAction(ShRibbonPolygonButtonStrategy::getIcon_(), "Polygon",
		this, SLOT(polygonActionClicked()));


	this->popupButton->setMenu(menu);

}

ShRibbonPolyLineButton::~ShRibbonPolyLineButton() {

}

void ShRibbonPolyLineButton::polyLineActionClicked() {
	this->changeStrategy(new ShRibbonPolyLineButtonStrategy);
	this->strategy->execute();
}

void ShRibbonPolyLineButton::rectangleActionClicked() {
	this->changeStrategy(new ShRibbonRectangleButtonStrategy);
	this->strategy->execute();
}

void ShRibbonPolyLineButton::polygonActionClicked() {
	this->changeStrategy(new ShRibbonPolygonButtonStrategy);
	this->strategy->execute();
}
