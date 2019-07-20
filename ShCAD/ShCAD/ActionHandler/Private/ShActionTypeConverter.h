
#ifndef _SHACTIONTYPECONVERTER_H
#define _SHACTIONTYPECONVERTER_H

#include "Base\ShVariable.h"
#include <qstring.h>

class ShActionTypeConverter {

public:
	ShActionTypeConverter();
	~ShActionTypeConverter();

	static QString convert(ActionType actionType);
	static ActionType convert(const QString &text);

};

#endif //_SHACTIONTYPECONVERTER_H