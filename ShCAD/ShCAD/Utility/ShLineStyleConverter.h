
#ifndef _SHLINESTYLECONVERTER_H
#define _SHLINESTYLECONVERTER_H

#include <qstring.h>

class ShLineStyle;

class ShLineStyleConverter {

public:
	ShLineStyleConverter();
	~ShLineStyleConverter();

	static QString getLineStyleText(unsigned short pattern);
	static QString getLineStyleShape(unsigned short pattern);

};

#endif //_SHLINESTYLECONVERTER_H