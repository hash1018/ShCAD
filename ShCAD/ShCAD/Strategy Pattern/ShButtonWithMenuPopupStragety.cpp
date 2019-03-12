
#include "ShButtonWithMenuPopupStrategy.h"
#include "ShDirectoryManager.h"
#include <qpixmap.h>
#include <qbitmap.h>
#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
#include "Singleton Pattern\ShWidgetManager.h"
#include "Interface\ShGraphicView.h"


ShButtonWithMenuPopupStrategy::ShButtonWithMenuPopupStrategy() {

}

ShButtonWithMenuPopupStrategy::~ShButtonWithMenuPopupStrategy() {


}

QIcon ShButtonWithMenuPopupStrategy::GetIcon(const QString& filePath) {

	QPixmap pix(filePath);
	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);

	QIcon icon(pix);

	return icon;
}

////////////////////////////////////////////////////////////////////////////////////

ShCircleButtonCenterRadiusStrategy::ShCircleButtonCenterRadiusStrategy() {

}

ShCircleButtonCenterRadiusStrategy::~ShCircleButtonCenterRadiusStrategy() {

}


void ShCircleButtonCenterRadiusStrategy::Do() {
	
	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawCircleCenterRadius);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShCircleButtonCenterRadiusStrategy::GetIcon(){

	QString path = ShDirectoryManager::GetImageUiPath();

	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\Circle\\Center-Radius.png");

}


/////////////////////////////////////////////////////////////////////////////////////

ShCircleButtonCenterDiameterStrategy::ShCircleButtonCenterDiameterStrategy() {

}

ShCircleButtonCenterDiameterStrategy::~ShCircleButtonCenterDiameterStrategy() {

}

void ShCircleButtonCenterDiameterStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawCircleCenterDiameter);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);

}

QIcon ShCircleButtonCenterDiameterStrategy::GetIcon(){

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\Circle\\Center-Diameter.png");
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////

ShCircleButtonTwoPointStrategy::ShCircleButtonTwoPointStrategy() {

}

ShCircleButtonTwoPointStrategy::~ShCircleButtonTwoPointStrategy() {

}

void ShCircleButtonTwoPointStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawCircleTwoPoint);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShCircleButtonTwoPointStrategy::GetIcon(){

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\Circle\\2Point.png");

}

////////////////////////////////////////////////////////////////////////////////////////////////////


ShCircleButtonThreePointStrategy::ShCircleButtonThreePointStrategy() {

}

ShCircleButtonThreePointStrategy::~ShCircleButtonThreePointStrategy() {

}

void ShCircleButtonThreePointStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawCircleThreePoint);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShCircleButtonThreePointStrategy::GetIcon(){

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\Circle\\3Point.png");
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

ShArcButtonThreePointStrategy::ShArcButtonThreePointStrategy() {

}

ShArcButtonThreePointStrategy::~ShArcButtonThreePointStrategy() {

}

void ShArcButtonThreePointStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcThreePoint);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShArcButtonThreePointStrategy::GetIcon() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\Arc\\3Point.png");
}


///////////////////////////////////////////////////////////////////////////////////////////////////

ShArcButtonStartCenterEndStrategy::ShArcButtonStartCenterEndStrategy() {

}

ShArcButtonStartCenterEndStrategy::~ShArcButtonStartCenterEndStrategy() {

}

void ShArcButtonStartCenterEndStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcStartCenterEnd);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShArcButtonStartCenterEndStrategy::GetIcon() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\Arc\\Start-Center-End.png");
}

//////////////////////////////////////////////////////////////////////////////////////////////////

ShArcButtonStartCenterAngleStrategy::ShArcButtonStartCenterAngleStrategy() {

}
	
ShArcButtonStartCenterAngleStrategy::~ShArcButtonStartCenterAngleStrategy() {

}

void ShArcButtonStartCenterAngleStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcStartCenterAngle);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShArcButtonStartCenterAngleStrategy::GetIcon() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\Arc\\Start-Center-Angle.png");
}

///////////////////////////////////////////////////////////////////////////////////////////////////


ShArcButtonStartCenterLengthStrategy::ShArcButtonStartCenterLengthStrategy() {

}

ShArcButtonStartCenterLengthStrategy::~ShArcButtonStartCenterLengthStrategy() {

}

void ShArcButtonStartCenterLengthStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcStartCenterLength);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShArcButtonStartCenterLengthStrategy::GetIcon() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\Arc\\Start-Center-Length.png");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////


ShArcButtonStartEndAngleStrategy::ShArcButtonStartEndAngleStrategy() {

}

ShArcButtonStartEndAngleStrategy::~ShArcButtonStartEndAngleStrategy() {

}

void ShArcButtonStartEndAngleStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcStartEndAngle);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShArcButtonStartEndAngleStrategy::GetIcon() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\Arc\\Start-End-Angle.png");
}

///////////////////////////////////////////////////////////////////////////////////////////////

ShArcButtonStartEndDirectionStrategy::ShArcButtonStartEndDirectionStrategy() {

}

ShArcButtonStartEndDirectionStrategy::~ShArcButtonStartEndDirectionStrategy() {

}

void ShArcButtonStartEndDirectionStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcStartEndDirection);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShArcButtonStartEndDirectionStrategy::GetIcon() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\Arc\\Start-End-Direction.png");
}

///////////////////////////////////////////////////////////////////////////////////////////


ShArcButtonStartEndRadiusStrategy::ShArcButtonStartEndRadiusStrategy() {

}

ShArcButtonStartEndRadiusStrategy::~ShArcButtonStartEndRadiusStrategy() {

}

void ShArcButtonStartEndRadiusStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcStartEndRadius);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShArcButtonStartEndRadiusStrategy::GetIcon() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\Arc\\Start-End-Radius.png");
}

/////////////////////////////////////////////////////////////////////////////////////////////

ShArcButtonCenterStartEndStrategy::ShArcButtonCenterStartEndStrategy() {

}

ShArcButtonCenterStartEndStrategy::~ShArcButtonCenterStartEndStrategy() {

}

void ShArcButtonCenterStartEndStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcCenterStartEnd);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShArcButtonCenterStartEndStrategy::GetIcon() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\Arc\\Center-Start-End.png");
}


///////////////////////////////////////////////////////////////////////////////////////////////

ShArcButtonCenterStartAngleStrategy::ShArcButtonCenterStartAngleStrategy() {

}


ShArcButtonCenterStartAngleStrategy::~ShArcButtonCenterStartAngleStrategy() {

}

void ShArcButtonCenterStartAngleStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcCenterStartAngle);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShArcButtonCenterStartAngleStrategy::GetIcon() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\Arc\\Center-Start-Angle.png");
}

////////////////////////////////////////////////////////////////////////////////////////////////

ShArcButtonCenterStartLengthStrategy::ShArcButtonCenterStartLengthStrategy() {

}

ShArcButtonCenterStartLengthStrategy::~ShArcButtonCenterStartLengthStrategy() {

}

void ShArcButtonCenterStartLengthStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcCenterStartLength);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShArcButtonCenterStartLengthStrategy::GetIcon() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\Arc\\Center-Start-Length.png");
}
