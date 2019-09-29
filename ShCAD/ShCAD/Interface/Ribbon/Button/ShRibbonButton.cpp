
#include "ShRibbonButton.h"
#include <qmenu.h>
#include "Interface\Private\ShRibbonButtonStrategy.h"
#include "Manager\ShLanguageManager.h"

ShAbstractRibbonButtonWithText::ShAbstractRibbonButtonWithText(QWidget *parent)
	:ShButtonWithMenuPopupWithText(parent), strategy(nullptr) {

	connect(this, &ShButtonWithMenuPopupWithText::pressed, this, &ShAbstractRibbonButtonWithText::buttonClicked);
}

ShAbstractRibbonButtonWithText::~ShAbstractRibbonButtonWithText() {

	if (this->strategy != nullptr)
		delete this->strategy;
}

void ShAbstractRibbonButtonWithText::buttonClicked() {

	if (this->strategy != nullptr)
		this->strategy->execute();

}

void ShAbstractRibbonButtonWithText::changeStrategy(ShRibbonButtonStrategy *strategy) {

	if (this->strategy != nullptr)
		delete this->strategy;

	this->strategy = strategy;
	this->setIcon(this->strategy->getIcon());
	this->setToolTip(this->strategy->getToolTip());

}

///////////////////////////////////////////////////////////////////////////////////

ShAbstractRibbonButton::ShAbstractRibbonButton(QWidget *parent)
	:ShButtonWithMenuPopup(parent), strategy(nullptr) {

	connect(this, &ShButtonWithMenuPopup::pressed, this, &ShAbstractRibbonButton::buttonClicked);
}

ShAbstractRibbonButton::~ShAbstractRibbonButton() {

	if (this->strategy != nullptr)
		delete this->strategy;
}

void ShAbstractRibbonButton::changeStrategy(ShRibbonButtonStrategy *strategy) {

	if (this->strategy != 0)
		delete this->strategy;

	this->strategy = strategy;
	this->setIcon(this->strategy->getIcon());
	this->setToolTip(this->strategy->getToolTip());
}

void ShAbstractRibbonButton::buttonClicked() {

	if (this->strategy != 0)
		this->strategy->execute();
}

///////////////////////////////////////////////////////////////////////////////////

ShRibbonCircleButton::ShRibbonCircleButton(QWidget *parent)
	:ShAbstractRibbonButtonWithText(parent) {

	this->setTextDirection(South);
	this->setText(shGetLanValue_ui("Draw/Circle"));
	this->setIconSize(this->size());

	this->strategy = new ShRibbonCircleButtonCenterRadiusStrategy;
	this->setIcon(this->strategy->getIcon());
	this->setToolTip(this->strategy->getToolTip());

	QMenu *menu = new QMenu(this->popupButton);
	menu->addAction(ShRibbonCircleButtonCenterRadiusStrategy::getIcon_(), shGetLanValue_ui("Draw/Circle,Center,Radius"), this, SLOT(centerRadiusActionClicked()));
	menu->addAction(ShRibbonCircleButtonCenterDiameterStrategy::getIcon_(), shGetLanValue_ui("Draw/Circle,Center,Diameter"), this, SLOT(centerDiameterActionClicked()));
	menu->addSeparator();
	menu->addAction(ShRibbonCircleButtonTwoPointStrategy::getIcon_(), shGetLanValue_ui("Draw/Circle,TwoPoints"), this, SLOT(twoPointActionClicked()));
	menu->addAction(ShRibbonCircleButtonThreePointStrategy::getIcon_(), shGetLanValue_ui("Draw/Circle,ThreePoints"), this, SLOT(threePointActionClicked()));

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
	:ShAbstractRibbonButtonWithText(parent) {

	this->setTextDirection(South);
	this->setText(shGetLanValue_ui("Draw/Arc"));
	this->setIconSize(this->size());

	this->strategy = new ShRibbonArcButtonThreePointStrategy;
	this->setIcon(this->strategy->getIcon());
	this->setToolTip(this->strategy->getToolTip());

	QMenu *menu = new QMenu(this->popupButton);
	menu->addAction(ShRibbonArcButtonThreePointStrategy::getIcon_(), shGetLanValue_ui("Draw/Arc,ThreePoints"),
		this, SLOT(threePointActionClicked()));

	menu->addSeparator();

	menu->addAction(ShRibbonArcButtonStartCenterEndStrategy::getIcon_(), shGetLanValue_ui("Draw/Arc,Start,Center,End"),
		this, SLOT(startCenterEndActionClicked()));

	menu->addAction(ShRibbonArcButtonStartCenterAngleStrategy::getIcon_(), shGetLanValue_ui("Draw/Arc,Start,Center,Angle"),
		this, SLOT(startCenterAngleActionClicked()));

	menu->addAction(ShRibbonArcButtonStartCenterLengthStrategy::getIcon_(), shGetLanValue_ui("Draw/Arc,Start,Center,Length"),
		this, SLOT(startCenterLengthActionClicked()));

	menu->addSeparator();

	menu->addAction(ShRibbonArcButtonStartEndAngleStrategy::getIcon_(), shGetLanValue_ui("Draw/Arc,Start,End,Angle"),
		this, SLOT(startEndAngleActionClicked()));

	menu->addAction(ShRibbonArcButtonStartEndDirectionStrategy::getIcon_(), shGetLanValue_ui("Draw/Arc,Start,End,Direction"),
		this, SLOT(startEndDirectionActionClicked()));

	menu->addAction(ShRibbonArcButtonStartEndRadiusStrategy::getIcon_(), shGetLanValue_ui("Draw/Arc,Start,End,Radius"),
		this, SLOT(startEndRadiusActionClicked()));

	menu->addSeparator();

	menu->addAction(ShRibbonArcButtonCenterStartEndStrategy::getIcon_(), shGetLanValue_ui("Draw/Arc,Center,Start,End"),
		this, SLOT(centerStartEndActionClicked()));

	menu->addAction(ShRibbonArcButtonCenterStartAngleStrategy::getIcon_(), shGetLanValue_ui("Draw/Arc,Center,Start,Angle"),
		this, SLOT(centerStartAngleActionClicked()));

	menu->addAction(ShRibbonArcButtonCenterStartLengthStrategy::getIcon_(), shGetLanValue_ui("Draw/Arc,Center,Start,Length"),
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
	:ShAbstractRibbonButtonWithText(parent) {

	this->setTextDirection(South);
	this->setText(shGetLanValue_ui("Draw/PolyLine"));
	this->setIconSize(this->size());

	this->strategy = new ShRibbonPolyLineButtonStrategy;
	this->setIcon(this->strategy->getIcon());
	this->setToolTip(this->strategy->getToolTip());

	QMenu *menu = new QMenu(this->popupButton);
	menu->addAction(ShRibbonPolyLineButtonStrategy::getIcon_(), shGetLanValue_ui("Draw/PolyLine"),
		this, SLOT(polyLineActionClicked()));
	menu->addAction(ShRibbonRectangleButtonStrategy::getIcon_(), shGetLanValue_ui("Draw/Rectangle"),
		this, SLOT(rectangleActionClicked()));
	menu->addAction(ShRibbonPolygonButtonStrategy::getIcon_(), shGetLanValue_ui("Draw/Polygon"),
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


////////////////////////////////////////////////////////////////////////

ShRibbonDimensionButton::ShRibbonDimensionButton(QWidget *parent)
	:ShAbstractRibbonButton(parent) {

	this->strategy = new ShRibbonDimLinearButtonStrategy;
	this->setIcon(this->strategy->getIcon());
	this->setToolTip(this->strategy->getToolTip());

	QMenu *menu = new QMenu(this->popupButton);
	menu->addAction(ShRibbonDimLinearButtonStrategy::getIcon_(), shGetLanValue_ui("Dim/Linear"),
		this, SLOT(dimLinearActionClicked()));
	menu->addAction(ShRibbonDimAlignedButtonStrategy::getIcon_(), shGetLanValue_ui("Dim/Aligned"),
		this, SLOT(dimAlignedActionClicked()));
	menu->addAction(ShRibbonDimAngularButtonStrategy::getIcon_(), shGetLanValue_ui("Dim/Angular"),
		this, SLOT(dimAngularActionClicked()));

	menu->addSeparator();

	menu->addAction(ShRibbonDimArcLengthButtonStrategy::getIcon_(), shGetLanValue_ui("Dim/ArcLength"),
		this, SLOT(dimArcLengthActionClicked()));
	menu->addAction(ShRibbonDimRadiusButtonStrategy::getIcon_(), shGetLanValue_ui("Dim/Radius"),
		this, SLOT(dimRadiusActionClicked()));
	menu->addAction(ShRibbonDimDiameterButtonStrategy::getIcon_(), shGetLanValue_ui("Dim/Diameter"),
		this, SLOT(dimDiameterActionClicked()));

	this->popupButton->setMenu(menu);
	
}

ShRibbonDimensionButton::~ShRibbonDimensionButton() {

}

void ShRibbonDimensionButton::dimLinearActionClicked() {

	this->changeStrategy(new ShRibbonDimLinearButtonStrategy);
	this->strategy->execute();
}

void ShRibbonDimensionButton::dimAlignedActionClicked() {

	this->changeStrategy(new ShRibbonDimAlignedButtonStrategy);
	this->strategy->execute();
}

void ShRibbonDimensionButton::dimAngularActionClicked() {

	this->changeStrategy(new ShRibbonDimAngularButtonStrategy);
	this->strategy->execute();
}

void ShRibbonDimensionButton::dimArcLengthActionClicked() {

	this->changeStrategy(new ShRibbonDimArcLengthButtonStrategy);
	this->strategy->execute();
}

void ShRibbonDimensionButton::dimRadiusActionClicked() {

	this->changeStrategy(new ShRibbonDimRadiusButtonStrategy);
	this->strategy->execute();
}

void ShRibbonDimensionButton::dimDiameterActionClicked() {

	this->changeStrategy(new ShRibbonDimDiameterButtonStrategy);
	this->strategy->execute();
}
