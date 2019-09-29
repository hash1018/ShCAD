
#include "ShRibbonButtonStrategy.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "Manager\ShCADWidgetManager.h"
#include "Interface\ShCADWidget.h"


ShRibbonButtonStrategy::ShRibbonButtonStrategy() {

}

ShRibbonButtonStrategy::~ShRibbonButtonStrategy() {


}


////////////////////////////////////////////////////////////////////////////////////

ShRibbonCircleButtonCenterRadiusStrategy::ShRibbonCircleButtonCenterRadiusStrategy() {

}

ShRibbonCircleButtonCenterRadiusStrategy::~ShRibbonCircleButtonCenterRadiusStrategy() {

}


void ShRibbonCircleButtonCenterRadiusStrategy::execute() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawCircleCenterRadius);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(strategy);
}

ShIcon ShRibbonCircleButtonCenterRadiusStrategy::getIcon() {

	return ShIcon(":/Image/Draw/Circle/Center-Radius.png");

}

ShIcon ShRibbonCircleButtonCenterRadiusStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/Circle/Center-Radius.png");
}

QString ShRibbonCircleButtonCenterRadiusStrategy::getToolTip() {

	return QString("Center, Radius \nCreates a circle using a center point and a radius");
}

/////////////////////////////////////////////////////////////////////////////////////

ShRibbonCircleButtonCenterDiameterStrategy::ShRibbonCircleButtonCenterDiameterStrategy() {

}

ShRibbonCircleButtonCenterDiameterStrategy::~ShRibbonCircleButtonCenterDiameterStrategy() {

}

void ShRibbonCircleButtonCenterDiameterStrategy::execute() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawCircleCenterDiameter);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(strategy);
}

ShIcon ShRibbonCircleButtonCenterDiameterStrategy::getIcon() {

	return ShIcon(":/Image/Draw/Circle/Center-Diameter.png");
}

ShIcon ShRibbonCircleButtonCenterDiameterStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/Circle/Center-Diameter.png");
}

QString ShRibbonCircleButtonCenterDiameterStrategy::getToolTip() {

	return QString("Center, Diameter \nCreates a circle using a center point and a diameter");
}

//////////////////////////////////////////////////////////////////////////////////////////////////

ShRibbonCircleButtonTwoPointStrategy::ShRibbonCircleButtonTwoPointStrategy() {

}

ShRibbonCircleButtonTwoPointStrategy::~ShRibbonCircleButtonTwoPointStrategy() {

}

void ShRibbonCircleButtonTwoPointStrategy::execute() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawCircleTwoPoint);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(strategy);
}

ShIcon ShRibbonCircleButtonTwoPointStrategy::getIcon() {

	return ShIcon(":/Image/Draw/Circle/2Point.png");
}


ShIcon ShRibbonCircleButtonTwoPointStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/Circle/2Point.png");
}

QString ShRibbonCircleButtonTwoPointStrategy::getToolTip() {

	return QString("2-Point \nCreates a circle using two endpoints of the diameter");
}

////////////////////////////////////////////////////////////////////////////////////////////////////


ShRibbonCircleButtonThreePointStrategy::ShRibbonCircleButtonThreePointStrategy() {

}

ShRibbonCircleButtonThreePointStrategy::~ShRibbonCircleButtonThreePointStrategy() {

}

void ShRibbonCircleButtonThreePointStrategy::execute() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawCircleThreePoint);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(strategy);
}

ShIcon ShRibbonCircleButtonThreePointStrategy::getIcon() {

	return ShIcon(":/Image/Draw/Circle/3Point.png");
}

ShIcon ShRibbonCircleButtonThreePointStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/Circle/3Point.png");
}

QString ShRibbonCircleButtonThreePointStrategy::getToolTip() {

	return QString("3-Point \nCreates a circle using three points on the circumference");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

ShRibbonArcButtonThreePointStrategy::ShRibbonArcButtonThreePointStrategy() {

}

ShRibbonArcButtonThreePointStrategy::~ShRibbonArcButtonThreePointStrategy() {

}

void ShRibbonArcButtonThreePointStrategy::execute() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcThreePoint);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(strategy);
}

ShIcon ShRibbonArcButtonThreePointStrategy::getIcon() {

	return ShIcon(":/Image/Draw/Arc/3Point.png");
}


ShIcon ShRibbonArcButtonThreePointStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/Arc/3Point.png");
}

QString ShRibbonArcButtonThreePointStrategy::getToolTip() {

	return QString("3-Point \nCreates an arc using three points");
}

///////////////////////////////////////////////////////////////////////////////////////////////////

ShRibbonArcButtonStartCenterEndStrategy::ShRibbonArcButtonStartCenterEndStrategy() {

}

ShRibbonArcButtonStartCenterEndStrategy::~ShRibbonArcButtonStartCenterEndStrategy() {

}

void ShRibbonArcButtonStartCenterEndStrategy::execute() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcStartCenterEnd);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(strategy);
}

ShIcon ShRibbonArcButtonStartCenterEndStrategy::getIcon() {

	return ShIcon(":/Image/Draw/Arc/Start-Center-End.png");
}


ShIcon ShRibbonArcButtonStartCenterEndStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/Arc/Start-Center-End.png");
}

QString ShRibbonArcButtonStartCenterEndStrategy::getToolTip() {

	return QString("Start, Center, End \nCreates an arc using a start point, center, and end point");
}

//////////////////////////////////////////////////////////////////////////////////////////////////

ShRibbonArcButtonStartCenterAngleStrategy::ShRibbonArcButtonStartCenterAngleStrategy() {

}

ShRibbonArcButtonStartCenterAngleStrategy::~ShRibbonArcButtonStartCenterAngleStrategy() {

}

void ShRibbonArcButtonStartCenterAngleStrategy::execute() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcStartCenterAngle);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(strategy);
}

ShIcon ShRibbonArcButtonStartCenterAngleStrategy::getIcon() {

	return ShIcon(":/Image/Draw/Arc/Start-Center-Angle.png");
}


ShIcon ShRibbonArcButtonStartCenterAngleStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/Arc/Start-Center-Angle.png");
}

QString ShRibbonArcButtonStartCenterAngleStrategy::getToolTip() {

	return QString("Start, Center, Angle \nCreates an arc using a start point, center, and an included angle");
}

///////////////////////////////////////////////////////////////////////////////////////////////////


ShRibbonArcButtonStartCenterLengthStrategy::ShRibbonArcButtonStartCenterLengthStrategy() {

}

ShRibbonArcButtonStartCenterLengthStrategy::~ShRibbonArcButtonStartCenterLengthStrategy() {

}

void ShRibbonArcButtonStartCenterLengthStrategy::execute() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcStartCenterLength);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(strategy);
}

ShIcon ShRibbonArcButtonStartCenterLengthStrategy::getIcon() {

	return ShIcon(":/Image/Draw/Arc/Start-Center-Length.png");
}


ShIcon ShRibbonArcButtonStartCenterLengthStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/Arc/Start-Center-Length.png");
}

QString ShRibbonArcButtonStartCenterLengthStrategy::getToolTip() {

	return QString("Start, Center, Length \nCreates an arc using a start point, center, and the length of a chord");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////


ShRibbonArcButtonStartEndAngleStrategy::ShRibbonArcButtonStartEndAngleStrategy() {

}

ShRibbonArcButtonStartEndAngleStrategy::~ShRibbonArcButtonStartEndAngleStrategy() {

}

void ShRibbonArcButtonStartEndAngleStrategy::execute() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcStartEndAngle);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(strategy);
}

ShIcon ShRibbonArcButtonStartEndAngleStrategy::getIcon() {

	return ShIcon(":/Image/Draw/Arc/Start-End-Angle.png");
}


ShIcon ShRibbonArcButtonStartEndAngleStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/Arc/Start-End-Angle.png");
}

QString ShRibbonArcButtonStartEndAngleStrategy::getToolTip() {

	return QString("Start, End, Angle \nCreates an arc using a start point, end point, and an included angle");
}

///////////////////////////////////////////////////////////////////////////////////////////////

ShRibbonArcButtonStartEndDirectionStrategy::ShRibbonArcButtonStartEndDirectionStrategy() {

}

ShRibbonArcButtonStartEndDirectionStrategy::~ShRibbonArcButtonStartEndDirectionStrategy() {

}

void ShRibbonArcButtonStartEndDirectionStrategy::execute() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcStartEndDirection);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(strategy);
}

ShIcon ShRibbonArcButtonStartEndDirectionStrategy::getIcon() {

	return ShIcon(":/Image/Draw/Arc/Start-End-Direction.png");
}


ShIcon ShRibbonArcButtonStartEndDirectionStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/Arc/Start-End-Direction.png");
}


QString ShRibbonArcButtonStartEndDirectionStrategy::getToolTip() {

	return QString("Start, End, Direction \nCreates an arc using a start point, end point, and a tangent direction at the start point");
}

///////////////////////////////////////////////////////////////////////////////////////////


ShRibbonArcButtonStartEndRadiusStrategy::ShRibbonArcButtonStartEndRadiusStrategy() {

}

ShRibbonArcButtonStartEndRadiusStrategy::~ShRibbonArcButtonStartEndRadiusStrategy() {

}

void ShRibbonArcButtonStartEndRadiusStrategy::execute() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcStartEndRadius);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(strategy);
}

ShIcon ShRibbonArcButtonStartEndRadiusStrategy::getIcon() {

	return ShIcon(":/Image/Draw/Arc/Start-End-Radius.png");
}


ShIcon ShRibbonArcButtonStartEndRadiusStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/Arc/Start-End-Radius.png");
}

QString ShRibbonArcButtonStartEndRadiusStrategy::getToolTip() {

	return QString("Start, End, Radius \nCreates an arc using a start point, end point, and a radius");
}

/////////////////////////////////////////////////////////////////////////////////////////////

ShRibbonArcButtonCenterStartEndStrategy::ShRibbonArcButtonCenterStartEndStrategy() {

}

ShRibbonArcButtonCenterStartEndStrategy::~ShRibbonArcButtonCenterStartEndStrategy() {

}

void ShRibbonArcButtonCenterStartEndStrategy::execute() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcCenterStartEnd);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(strategy);
}

ShIcon ShRibbonArcButtonCenterStartEndStrategy::getIcon() {

	return ShIcon(":/Image/Draw/Arc/Center-Start-End.png");
}


ShIcon ShRibbonArcButtonCenterStartEndStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/Arc/Center-Start-End.png");
}


QString ShRibbonArcButtonCenterStartEndStrategy::getToolTip() {

	return QString("Center, Start, End \nCreates an arc using a center point, start point, and a third point that determines the end point");
}

///////////////////////////////////////////////////////////////////////////////////////////////

ShRibbonArcButtonCenterStartAngleStrategy::ShRibbonArcButtonCenterStartAngleStrategy() {

}


ShRibbonArcButtonCenterStartAngleStrategy::~ShRibbonArcButtonCenterStartAngleStrategy() {

}

void ShRibbonArcButtonCenterStartAngleStrategy::execute() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcCenterStartAngle);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(strategy);
}

ShIcon ShRibbonArcButtonCenterStartAngleStrategy::getIcon() {

	return ShIcon(":/Image/Draw/Arc/Center-Start-Angle.png");
}


ShIcon ShRibbonArcButtonCenterStartAngleStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/Arc/Center-Start-Angle.png");
}

QString ShRibbonArcButtonCenterStartAngleStrategy::getToolTip() {

	return QString("Center, Start, Angle \nCreates an arc using a center point, start point, and an included angle");
}

////////////////////////////////////////////////////////////////////////////////////////////////

ShRibbonArcButtonCenterStartLengthStrategy::ShRibbonArcButtonCenterStartLengthStrategy() {

}

ShRibbonArcButtonCenterStartLengthStrategy::~ShRibbonArcButtonCenterStartLengthStrategy() {

}

void ShRibbonArcButtonCenterStartLengthStrategy::execute() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcCenterStartLength);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(strategy);
}

ShIcon ShRibbonArcButtonCenterStartLengthStrategy::getIcon() {

	return ShIcon(":/Image/Draw/Arc/Center-Start-Length.png");
}


ShIcon ShRibbonArcButtonCenterStartLengthStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/Arc/Center-Start-Length.png");
}


QString ShRibbonArcButtonCenterStartLengthStrategy::getToolTip() {

	return QString("Center, Start, Length \nCreates an arc using a center point, start point, and a length of the chord");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

ShRibbonRectangleButtonStrategy::ShRibbonRectangleButtonStrategy() {

}

ShRibbonRectangleButtonStrategy::~ShRibbonRectangleButtonStrategy() {

}

void ShRibbonRectangleButtonStrategy::execute() {


}

ShIcon ShRibbonRectangleButtonStrategy::getIcon() {

	return ShIcon(":/Image/Draw/PolyLine/Rectangle.png");
}

ShIcon ShRibbonRectangleButtonStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/PolyLine/Rectangle.png");
}

QString ShRibbonRectangleButtonStrategy::getToolTip() {

	return QString("Rectangle \nCreates a rectangular polyline");
}

///////////////////////////////////////////////////////////////////////////////////////////////

ShRibbonPolygonButtonStrategy::ShRibbonPolygonButtonStrategy() {

}

ShRibbonPolygonButtonStrategy::~ShRibbonPolygonButtonStrategy() {

}

void ShRibbonPolygonButtonStrategy::execute() {


}

ShIcon ShRibbonPolygonButtonStrategy::getIcon() {

	return ShIcon(":/Image/Draw/PolyLine/Polygon.png");
}

ShIcon ShRibbonPolygonButtonStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/PolyLine/Polygon.png");
}

QString ShRibbonPolygonButtonStrategy::getToolTip() {

	return QString("Polygon \nCreates an equilateral closed polyline");
}

///////////////////////////////////////////////////////////////////////////////////////////////

ShRibbonPolyLineButtonStrategy::ShRibbonPolyLineButtonStrategy() {

}

ShRibbonPolyLineButtonStrategy::~ShRibbonPolyLineButtonStrategy() {

}


void ShRibbonPolyLineButtonStrategy::execute() {


}

ShIcon ShRibbonPolyLineButtonStrategy::getIcon() {

	return ShIcon(":/Image/Draw/PolyLine/PolyLine.png");
}


ShIcon ShRibbonPolyLineButtonStrategy::getIcon_() {

	return ShIcon(":/Image/Draw/PolyLine/PolyLine.png");
}

QString ShRibbonPolyLineButtonStrategy::getToolTip() {

	return QString("PolyLine \nCreates a polyline");
}


//////////////////////////////////////////////////////////////////////

ShRibbonDimLinearButtonStrategy::ShRibbonDimLinearButtonStrategy() {


}

ShRibbonDimLinearButtonStrategy::~ShRibbonDimLinearButtonStrategy() {

}

void ShRibbonDimLinearButtonStrategy::execute() {

	if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawDimLinear);
	ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(strategy);
}

ShIcon ShRibbonDimLinearButtonStrategy::getIcon() {

	return ShIcon(":/Image/Dimension/DimLinear.png");
}

QString ShRibbonDimLinearButtonStrategy::getToolTip() {

	return QString("DimLinear \nCreates a dimLinear");
}

ShIcon ShRibbonDimLinearButtonStrategy::getIcon_() {

	return ShIcon(":/Image/Dimension/DimLinear.png");
}

//////////////////////////////////////////////////////////////////////

ShRibbonDimAlignedButtonStrategy::ShRibbonDimAlignedButtonStrategy() {


}

ShRibbonDimAlignedButtonStrategy::~ShRibbonDimAlignedButtonStrategy() {

}

void ShRibbonDimAlignedButtonStrategy::execute() {

}

ShIcon ShRibbonDimAlignedButtonStrategy::getIcon() {

	return ShIcon(":/Image/Dimension/DimAligned.png");
}

QString ShRibbonDimAlignedButtonStrategy::getToolTip() {

	return QString("DimAligned \nCreates a dimAligned");
}

ShIcon ShRibbonDimAlignedButtonStrategy::getIcon_() {

	return ShIcon(":/Image/Dimension/DimAligned.png");
}

//////////////////////////////////////////////////////////////////////

ShRibbonDimRadiusButtonStrategy::ShRibbonDimRadiusButtonStrategy() {


}

ShRibbonDimRadiusButtonStrategy::~ShRibbonDimRadiusButtonStrategy() {

}

void ShRibbonDimRadiusButtonStrategy::execute() {

}

ShIcon ShRibbonDimRadiusButtonStrategy::getIcon() {

	return ShIcon(":/Image/Dimension/DimRadius.png");
}

QString ShRibbonDimRadiusButtonStrategy::getToolTip() {

	return QString("DimRadius \nCreates a dimRadius");
}

ShIcon ShRibbonDimRadiusButtonStrategy::getIcon_() {

	return ShIcon(":/Image/Dimension/DimRadius.png");
}

//////////////////////////////////////////////////////////////////////

ShRibbonDimDiameterButtonStrategy::ShRibbonDimDiameterButtonStrategy() {


}

ShRibbonDimDiameterButtonStrategy::~ShRibbonDimDiameterButtonStrategy() {

}

void ShRibbonDimDiameterButtonStrategy::execute() {

}

ShIcon ShRibbonDimDiameterButtonStrategy::getIcon() {

	return ShIcon(":/Image/Dimension/DimDiameter.png");
}

QString ShRibbonDimDiameterButtonStrategy::getToolTip() {

	return QString("DimDiameter \nCreates a dimDiameter");
}

ShIcon ShRibbonDimDiameterButtonStrategy::getIcon_() {

	return ShIcon(":/Image/Dimension/DimDiameter.png");
}


//////////////////////////////////////////////////////////////////////

ShRibbonDimAngularButtonStrategy::ShRibbonDimAngularButtonStrategy() {


}

ShRibbonDimAngularButtonStrategy::~ShRibbonDimAngularButtonStrategy() {

}

void ShRibbonDimAngularButtonStrategy::execute() {

}

ShIcon ShRibbonDimAngularButtonStrategy::getIcon() {

	return ShIcon(":/Image/Dimension/DimAngular.png");
}

QString ShRibbonDimAngularButtonStrategy::getToolTip() {

	return QString("DimAngular \nCreates a dimAngular");
}

ShIcon ShRibbonDimAngularButtonStrategy::getIcon_() {

	return ShIcon(":/Image/Dimension/DimAngular.png");
}


//////////////////////////////////////////////////////////////////////

ShRibbonDimArcLengthButtonStrategy::ShRibbonDimArcLengthButtonStrategy() {


}

ShRibbonDimArcLengthButtonStrategy::~ShRibbonDimArcLengthButtonStrategy() {

}

void ShRibbonDimArcLengthButtonStrategy::execute() {

}

ShIcon ShRibbonDimArcLengthButtonStrategy::getIcon() {

	return ShIcon(":/Image/Dimension/DimArcLength.png");
}

QString ShRibbonDimArcLengthButtonStrategy::getToolTip() {

	return QString("DimArcLength \nCreates dimArcLength");
}

ShIcon ShRibbonDimArcLengthButtonStrategy::getIcon_() {

	return ShIcon(":/Image/Dimension/DimArcLength.png");
}
