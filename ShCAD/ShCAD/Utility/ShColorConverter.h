
#ifndef _SHCOLORCONVERTER_H
#define _SHCOLORCONVERTER_H

#include <qpixmap.h>
#include <qstring.h>

class ShColor;

class ShColorConverter {

public:
	ShColorConverter();
	~ShColorConverter();

	static QPixmap convertColorImage(const ShColor &color, int width, int height);
	static QString convertColorText(const ShColor &color);

};

#endif //_SHCOLORCONVERTER_H