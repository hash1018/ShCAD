

#ifndef _SHLINESTYLELIST_H
#define _SHLINESTYLELIST_H

#include <qlist.h>
#include "ShLineStyle.h"

class ShLineStyleList {

private:
	QList<ShLineStyle> list;

private:
	ShLineStyleList();
	~ShLineStyleList();

	static ShLineStyleList instance;

public:
	static ShLineStyleList* getInstance();

	int search(const ShLineStyle &lineStyle);
	int search(unsigned short pattern);


	inline int getSize() const { return this->list.size(); }
	inline ShLineStyle getLineStyle(int index) const { return this->list.at(index); }
};

#endif //_SHLINESTYLELIST_H