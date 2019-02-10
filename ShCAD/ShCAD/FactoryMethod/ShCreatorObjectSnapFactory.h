

#ifndef _SHCREATOROBJECTSNAPFACTORY_H
#define _SHCREATOROBJECTSNAPFACTORY_H

#include "ShVariable.h"
class ShObjectSnapState;
class ShGraphicView;
class ShCreatorObjectSnapFactory {

public:
	ShCreatorObjectSnapFactory();
	~ShCreatorObjectSnapFactory();

	static ShObjectSnapState* Create(ObjectSnap objectSnap, ShGraphicView *view);

};

#endif //_SHCREATOROBJECTSNAPFACTORY_H