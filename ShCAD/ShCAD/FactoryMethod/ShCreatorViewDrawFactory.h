

#ifndef _SHCREATORVIEWDRAWFACTORY_H
#define _SHCREATORVIEWDRAWFACTORY_H

#include "ShVariable.h"

class ShViewDrawStrategy;
class ShGraphicView;
class QPainter;
class ShCreatorViewDrawFactory {

public:
	ShCreatorViewDrawFactory();
	~ShCreatorViewDrawFactory();

	static ShViewDrawStrategy* Create(ShGraphicView *view, QPainter *painter, DrawType drawType);

};

#endif //_SHCREATORVIEWDRAWFACTORY_H