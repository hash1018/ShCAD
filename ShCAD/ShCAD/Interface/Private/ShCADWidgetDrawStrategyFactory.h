

#ifndef _SHCADWIDGETDRAWSTRATEGYFACTORY_H
#define _SHCADWIDGETDRAWSTRATEGYFACTORY_H

#include "Base\ShVariable.h"

class ShCADWidget;
class ShCADWidgetDrawStrategy;
class QPainter;

class ShCADWidgetDrawStrategyFactory {

public:
	ShCADWidgetDrawStrategyFactory();
	~ShCADWidgetDrawStrategyFactory();

	static ShCADWidgetDrawStrategy* create(ShCADWidget *widget, QPainter *painter, DrawType drawType);

};

#endif //_SHCADWIDGETDRAWSTRATEGYFACTORY_H