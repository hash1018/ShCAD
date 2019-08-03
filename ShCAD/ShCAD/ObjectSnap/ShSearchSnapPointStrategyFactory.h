
#ifndef _SHSEARCHSNAPPOINTSTRATEGYFACTORY_H
#define _SHSEARCHSNAPPOINTSTRATEGYFACTORY_H

#include "Base\ShVariable.h"

class ShCADWidget;
class ShSearchSnapPointStrategy;

class ShSearchSnapPointStrategyFactory {

public:
	ShSearchSnapPointStrategyFactory();
	~ShSearchSnapPointStrategyFactory();

	static ShSearchSnapPointStrategy* create(ObjectSnap objectSnap, ShCADWidget *widget);

};

#endif //_SHSEARCHSNAPPOINTSTRATEGYFACTORY_H