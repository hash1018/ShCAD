
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

QIcon ShButtonWithMenuPopupStrategy::GetIcon_(const QString& filePath) {

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

QIcon ShCircleButtonCenterRadiusStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();

	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\Circle\\Center-Radius.png");
}

QString ShCircleButtonCenterRadiusStrategy::GetToolTip() {

	return QString("Center, Radius \nCreates a circle using a center point and a radius");
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

QIcon ShCircleButtonCenterDiameterStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\Circle\\Center-Diameter.png");

}

QString ShCircleButtonCenterDiameterStrategy::GetToolTip() {

	return QString("Center, Diameter \nCreates a circle using a center point and a diameter");
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


QIcon ShCircleButtonTwoPointStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\Circle\\2Point.png");

}

QString ShCircleButtonTwoPointStrategy::GetToolTip() {

	return QString("2-Point \nCreates a circle using two endpoints of the diameter");
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

QIcon ShCircleButtonThreePointStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\Circle\\3Point.png");

}

QString ShCircleButtonThreePointStrategy::GetToolTip() {

	return QString("3-Point \nCreates a circle using three points on the circumference");
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


QIcon ShArcButtonThreePointStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\Arc\\3Point.png");
}

QString ShArcButtonThreePointStrategy::GetToolTip() {

	return QString("3-Point \nCreates an arc using three points");
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


QIcon ShArcButtonStartCenterEndStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\Arc\\Start-Center-End.png");
}

QString ShArcButtonStartCenterEndStrategy::GetToolTip() {

	return QString("Start, Center, End \nCreates an arc using a start point, center, and end point");
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


QIcon ShArcButtonStartCenterAngleStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\Arc\\Start-Center-Angle.png");
}

QString ShArcButtonStartCenterAngleStrategy::GetToolTip() {

	return QString("Start, Center, Angle \nCreates an arc using a start point, center, and an included angle");
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


QIcon ShArcButtonStartCenterLengthStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\Arc\\Start-Center-Length.png");
}

QString ShArcButtonStartCenterLengthStrategy::GetToolTip() {

	return QString("Start, Center, Length \nCreates an arc using a start point, center, and the length of a chord");
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


QIcon ShArcButtonStartEndAngleStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\Arc\\Start-End-Angle.png");
}

QString ShArcButtonStartEndAngleStrategy::GetToolTip() {

	return QString("Start, End, Angle \nCreates an arc using a start point, end point, and an included angle");
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


QIcon ShArcButtonStartEndDirectionStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\Arc\\Start-End-Direction.png");
}


QString ShArcButtonStartEndDirectionStrategy::GetToolTip() {

	return QString("Start, End, Direction \nCreates an arc using a start point, end point, and a tangent direction at the start point");
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


QIcon ShArcButtonStartEndRadiusStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\Arc\\Start-End-Radius.png");
}

QString ShArcButtonStartEndRadiusStrategy::GetToolTip() {

	return QString("Start, End, Radius \nCreates an arc using a start point, end point, and a radius");
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


QIcon ShArcButtonCenterStartEndStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\Arc\\Center-Start-End.png");
}


QString ShArcButtonCenterStartEndStrategy::GetToolTip() {

	return QString("Center, Start, End \nCreates an arc using a center point, start point, and a third point that determines the end point");
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


QIcon ShArcButtonCenterStartAngleStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\Arc\\Center-Start-Angle.png");
}

QString ShArcButtonCenterStartAngleStrategy::GetToolTip() {

	return QString("Center, Start, Angle \nCreates an arc using a center point, start point, and an included angle");
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


QIcon ShArcButtonCenterStartLengthStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\Arc\\Center-Start-Length.png");
}


QString ShArcButtonCenterStartLengthStrategy::GetToolTip() {

	return QString("Center, Start, Length \nCreates an arc using a center point, start point, and a length of the chord");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

ShRectangleButtonStrategy::ShRectangleButtonStrategy() {

}

ShRectangleButtonStrategy::~ShRectangleButtonStrategy() {

}

void ShRectangleButtonStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawRectangle);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShRectangleButtonStrategy::GetIcon() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\PolyLine\\Rectangle.png");

}

QIcon ShRectangleButtonStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\PolyLine\\Rectangle.png");
}

QString ShRectangleButtonStrategy::GetToolTip() {

	return QString("Rectangle \nCreates a rectangular polyline");
}

///////////////////////////////////////////////////////////////////////////////////////////////

ShPolygonButtonStrategy::ShPolygonButtonStrategy() {

}

ShPolygonButtonStrategy::~ShPolygonButtonStrategy() {

}

void ShPolygonButtonStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawPolygon);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShPolygonButtonStrategy::GetIcon() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\PolyLine\\Polygon.png");
}

QIcon ShPolygonButtonStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\PolyLine\\Polygon.png");
}

QString ShPolygonButtonStrategy::GetToolTip() {

	return QString("Polygon \nCreates an equilateral closed polyline");
}

///////////////////////////////////////////////////////////////////////////////////////////////

ShPolyLineButtonStrategy::ShPolyLineButtonStrategy() {

}

ShPolyLineButtonStrategy::	~ShPolyLineButtonStrategy() {

}


void ShPolyLineButtonStrategy::Do() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawPolyLine);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

QIcon ShPolyLineButtonStrategy::GetIcon() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon(path + "\\PolyLine\\PolyLine.png");
}


QIcon ShPolyLineButtonStrategy::GetIcon_() {

	QString path = ShDirectoryManager::GetImageUiPath();
	return ShButtonWithMenuPopupStrategy::GetIcon_(path + "\\PolyLine\\PolyLine.png");
}

QString ShPolyLineButtonStrategy::GetToolTip() {

	return QString("PolyLine \nCreates a polyline");
}