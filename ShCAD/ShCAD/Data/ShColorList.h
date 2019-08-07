
#ifndef _SHCOLORLIST_H
#define _SHCOLORLIST_H

#include <qlist.h>
#include "ShColor.h"
#include <qpixmap.h>

class ShColorList {

private:
	QList<ShColor> list;

private:
	ShColorList();
	~ShColorList();

	static ShColorList instance;

public:
	static ShColorList* getInstance();

	QPixmap getColorImage(const ShColor &color, int width, int height);
	QPixmap getColorImage(int width, int height, int index);
	QString getColorText(int index);

	int search(const ShColor &color);
	void add(const ShColor &color);

	inline int getSize() const { return this->list.size(); }
	inline ShColor getColor(int index) { return this->list.at(index); }

};

#endif //_SHCOLORLIST_H