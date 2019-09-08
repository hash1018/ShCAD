
#ifndef _SHCURSORSHAPE_H
#define _SHCURSORSHAPE_H

#include <qcursor.h>

class ShCursorShape {

public:
	enum CursorType {
		Nothing,
		Default,
		Drawing,
		Selecting,
	};

private:
	ShCursorShape();
	~ShCursorShape();

	static ShCursorShape instance;

public:
	static ShCursorShape* getInstance();

	static QCursor getCursor(CursorType type);
};



#endif //_SHCURSORSHAPE_H