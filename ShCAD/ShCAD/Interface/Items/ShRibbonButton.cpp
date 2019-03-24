

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
	menu->addAction(ShCircleButtonCenterRadiusStrategy::GetIcon_(), "Center, Radius", this, SLOT(CenterRadiusActionClicked()));
	menu->addAction(ShCircleButtonCenterDiameterStrategy::GetIcon_(), "Center, Diameter", this, SLOT(CenterDiameterActionClicked()));
	menu->addSeparator();
	menu->addAction(ShCircleButtonTwoPointStrategy::GetIcon_(), "2-Point", this, SLOT(TwoPointActionClicked()));
	menu->addAction(ShCircleButtonThreePointStrategy::GetIcon_(), "3-Point", this, SLOT(ThreePointActionClicked()));

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

	this->strategy = new ShArcButtonThreePointStrategy;
	this->SetIcon(this->strategy->GetIcon());

	QMenu *menu = new QMenu(this->popupButton);
	menu->addAction(ShArcButtonThreePointStrategy::GetIcon_(), "3-Point", 
		this, SLOT(ThreePointActionClicked()));

	menu->addSeparator();

	menu->addAction(ShArcButtonStartCenterEndStrategy::GetIcon_(), "Start, Center, End", 
		this, SLOT(StartCenterEndActionClicked()));

	menu->addAction(ShArcButtonStartCenterAngleStrategy::GetIcon_(), "Start, Center, Angle",
		this, SLOT(StartCenterAngleActionClicked()));

	menu->addAction(ShArcButtonStartCenterLengthStrategy::GetIcon_(), "Start, Center, Length",
		this, SLOT(StartCenterLengthActionClicked()));

	menu->addSeparator();

	menu->addAction(ShArcButtonStartEndAngleStrategy::GetIcon_(), "Start, End, Angle",
		this, SLOT(StartEndAngleActionClicked()));

	menu->addAction(ShArcButtonStartEndDirectionStrategy::GetIcon_(), "Start, End, Direction",
		this, SLOT(StartEndDirectionActionClicked()));

	menu->addAction(ShArcButtonStartEndRadiusStrategy::GetIcon_(), "Start, End, Radius",
		this, SLOT(StartEndRadiusActionClicked()));

	menu->addSeparator();

	menu->addAction(ShArcButtonCenterStartEndStrategy::GetIcon_(),"Center, Start, End", 
		this, SLOT(CenterStartEndActionClicked()));

	menu->addAction(ShArcButtonCenterStartAngleStrategy::GetIcon_(),"Center, Start, Angle", 
		this, SLOT(CenterStartAngleActionClicked()));

	menu->addAction(ShArcButtonCenterStartLengthStrategy::GetIcon_(), "Center, Start, Length",
		this, SLOT(CenterStartLengthActionClicked()));

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

/////////////////////////////////////////////////////////////////////////////

ShRibbonPolyLineButton::ShRibbonPolyLineButton(QWidget *parent)
	:ShAbstractRibbonButton(parent) {

	this->strategy = new ShPolyLineButtonStrategy;
	this->SetIcon(this->strategy->GetIcon());

	QMenu *menu = new QMenu(this->popupButton);
	menu->addAction(ShPolyLineButtonStrategy::GetIcon_(), "PolyLine",
		this, SLOT(PolyLineActionClicked()));
	menu->addAction(ShRectangleButtonStrategy::GetIcon_(), "Rectangle",
		this, SLOT(RectangleActionClicked()));
	menu->addAction(ShPolygonButtonStrategy::GetIcon_(), "Polygon",
		this, SLOT(PolygonActionClicked()));


	this->popupButton->setMenu(menu);

}

ShRibbonPolyLineButton::~ShRibbonPolyLineButton() {

}

void ShRibbonPolyLineButton::PolyLineActionClicked() {
	this->ChangeStrategy(new ShPolyLineButtonStrategy);
	this->strategy->Do();
}

void ShRibbonPolyLineButton::RectangleActionClicked() {
	this->ChangeStrategy(new ShRectangleButtonStrategy);
	this->strategy->Do();
}

void ShRibbonPolyLineButton::PolygonActionClicked() {
	this->ChangeStrategy(new ShPolygonButtonStrategy);
	this->strategy->Do();
}