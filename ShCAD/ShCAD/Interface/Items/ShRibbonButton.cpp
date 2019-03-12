

#include "ShRibbonButton.h"
#include "Strategy Pattern\ShButtonWithMenuPopupStrategy.h"
#include <qmenu.h>

ShAbstractRibbonButton::ShAbstractRibbonButton(QWidget *parent)
	:ShButtonWithMenuPopup(parent), strategy(0) {



	connect(this, &ShButtonWithMenuPopup::pressed, this, &ShAbstractRibbonButton::ButtonClicked);
}

ShAbstractRibbonButton::~ShAbstractRibbonButton() {

	if (this->strategy != 0)
		delete this->strategy;

}

void ShAbstractRibbonButton::ChangeStrategy(ShButtonWithMenuPopupStrategy *strategy) {

	if (this->strategy != 0)
		delete this->strategy;

	this->strategy = strategy;
	this->SetIcon(this->strategy->GetIcon());

}


void ShAbstractRibbonButton::ButtonClicked() {

	if (this->strategy != 0)
		this->strategy->Do();
}

////////////////////////////////////////////////////////////////////////////////

ShRibbonCircleButton::ShRibbonCircleButton(QWidget *parent)
	:ShAbstractRibbonButton(parent) {

	this->strategy = new ShCircleButtonCenterRadiusStrategy;
	this->SetIcon(this->strategy->GetIcon());

	QMenu *menu = new QMenu(this->popupButton);
	menu->addAction("Center, Radius", this, SLOT(CenterRadiusActionClicked()));
	menu->addAction("Center, Diameter", this, SLOT(CenterDiameterActionClicked()));
	menu->addSeparator();
	menu->addAction("2-Point", this, SLOT(TwoPointActionClicked()));
	menu->addAction("3-Point", this, SLOT(ThreePointActionClicked()));

	this->popupButton->setMenu(menu);

	
	
}

ShRibbonCircleButton::~ShRibbonCircleButton() {

}

void ShRibbonCircleButton::CenterRadiusActionClicked() {
	this->ChangeStrategy(new ShCircleButtonCenterRadiusStrategy);
	this->strategy->Do();
}

void ShRibbonCircleButton::CenterDiameterActionClicked() {
	this->ChangeStrategy(new ShCircleButtonCenterDiameterStrategy);
	this->strategy->Do();
}

void ShRibbonCircleButton::TwoPointActionClicked() {
	this->ChangeStrategy(new ShCircleButtonTwoPointStrategy);
	this->strategy->Do();
}

void ShRibbonCircleButton::ThreePointActionClicked() {
	this->ChangeStrategy(new ShCircleButtonThreePointStrategy);
	this->strategy->Do();
}

//////////////////////////////////////////////////////////////////////////////////////

ShRibbonArcButton::ShRibbonArcButton(QWidget *parent)
	:ShAbstractRibbonButton(parent) {

	this->strategy = new ShArcButtonCenterStartEndStrategy;
	this->SetIcon(this->strategy->GetIcon());

	QMenu *menu = new QMenu(this->popupButton);
	menu->addAction("3-Point", this, SLOT(ThreePointActionClicked()));
	menu->addSeparator();
	menu->addAction("Start, Center, End", this, SLOT(StartCenterEndActionClicked()));
	menu->addAction("Start, Center, Angle", this, SLOT(StartCenterAngleActionClicked()));
	menu->addAction("Start, Center, Length", this, SLOT(StartCenterLengthActionClicked()));
	menu->addSeparator();
	menu->addAction("Start, End, Angle", this, SLOT(StartEndAngleActionClicked()));
	menu->addAction("Start, End, Direction", this, SLOT(StartEndDirectionActionClicked()));
	menu->addAction("Start, End, Radius", this, SLOT(StartEndRadiusActionClicked()));
	menu->addSeparator();
	menu->addAction("Center, Start, End", this, SLOT(CenterStartEndActionClicked()));
	menu->addAction("Center, Start, Angle", this, SLOT(CenterStartAngleActionClicked()));
	menu->addAction("Center, Start, Length", this, SLOT(CenterStartLengthActionClicked()));

	this->popupButton->setMenu(menu);
}

ShRibbonArcButton::~ShRibbonArcButton() {


}

void ShRibbonArcButton::ThreePointActionClicked() {
	this->ChangeStrategy(new ShArcButtonThreePointStrategy);
	this->strategy->Do();
}

void ShRibbonArcButton::StartCenterEndActionClicked() {
	this->ChangeStrategy(new ShArcButtonStartCenterEndStrategy);
	this->strategy->Do();
}

void ShRibbonArcButton::StartCenterAngleActionClicked() {
	this->ChangeStrategy(new ShArcButtonStartCenterAngleStrategy);
	this->strategy->Do();
}

void ShRibbonArcButton::StartCenterLengthActionClicked() {
	this->ChangeStrategy(new ShArcButtonStartCenterLengthStrategy);
	this->strategy->Do();
}

void ShRibbonArcButton::StartEndAngleActionClicked() {
	this->ChangeStrategy(new ShArcButtonStartEndAngleStrategy);
	this->strategy->Do();
}

void ShRibbonArcButton::StartEndDirectionActionClicked() {
	this->ChangeStrategy(new ShArcButtonStartEndDirectionStrategy);
	this->strategy->Do();
}

void ShRibbonArcButton::StartEndRadiusActionClicked() {
	this->ChangeStrategy(new ShArcButtonStartEndRadiusStrategy);
	this->strategy->Do();
}

void ShRibbonArcButton::CenterStartEndActionClicked() {
	this->ChangeStrategy(new ShArcButtonCenterStartEndStrategy);
	this->strategy->Do();
}

void ShRibbonArcButton::CenterStartAngleActionClicked() {
	this->ChangeStrategy(new ShArcButtonCenterStartAngleStrategy);
	this->strategy->Do();
}

void ShRibbonArcButton::CenterStartLengthActionClicked() {
	this->ChangeStrategy(new ShArcButtonCenterStartLengthStrategy);
	this->strategy->Do();
}