
#ifndef _SHOBJECTSNAPCOMMANDFACTORY_H
#define _SHOBJECTSNAPCOMMANDFACTORY_H
#include <qstring.h>
#include "Base\ShVariable.h"
class ShObjectSnapCommandFactory {

public:
	ShObjectSnapCommandFactory();
	~ShObjectSnapCommandFactory();

	static QString create(ObjectSnap objectSnap);

};

#endif //_SHOBJECTSNAPCOMMANDFACTORY_H