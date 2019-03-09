

#ifndef _SHCREATOROBJECTSNAPFACTORY_H
#define _SHCREATOROBJECTSNAPFACTORY_H

#include "ShVariable.h"
class ShObjectSnapStrategy;
class ShGraphicView;
class ShCreatorObjectSnapFactory {

public:
	ShCreatorObjectSnapFactory();
	~ShCreatorObjectSnapFactory();

	static ShObjectSnapStrategy* Create(ObjectSnap objectSnap, ShGraphicView *view);

};

#endif //_SHCREATOROBJECTSNAPFACTORY_H