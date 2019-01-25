

#ifndef _SHCOLORCOMBOLIST_H
#define _SHCOLORCOMBOLIST_H

#include <qlist.h>
#include "ShPropertyData.h"
#include <qpixmap.h>


class ShColorComboList {


private:
	QList<ShColor> list;
	

private:
	ShColorComboList();
	~ShColorComboList();

	static ShColorComboList instance;

public:
	static ShColorComboList* GetInstance();


	QPixmap GetColorImage(const ShColor& color, int width, int height);
	QPixmap GetColorImage(int width, int height,int index);
	QString GetColorText(int index);
	

	int Search(const ShColor& color);
	void Add(const ShColor& color);

	inline int GetSize() const { return this->list.size(); }
	inline ShColor GetColor(int index) const { return this->list.at(index); }
	

};

#endif //_SHCOLORCOMBOLIST_H