
#ifndef _SHCURSORSHAPE_H
#define _SHCURSORSHAPE_H

#include <qcursor.h>
#include "Base\ShSingleton.h"

class ShCursorShape {

	DeclareSingleton(ShCursorShape)

public:
	enum CursorType {
		Nothing,
		Default,
		Drawing,
		Selecting,
	};

public:
	static QCursor getCursor(CursorType type);
};



#endif //_SHCURSORSHAPE_H