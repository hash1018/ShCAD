

#ifndef _SHLINESTYLECOMBOLIST_H
#define _SHLINESTYLECOMBOLIST_H

#include <qlist.h>
#include "ShPropertyData.h"

class ShLineStyleComboList {

private:
	QList<ShLineStyle> list;

private:
	ShLineStyleComboList();
	~ShLineStyleComboList();

	static ShLineStyleComboList instance;

	QString GetLineStyleShape(unsigned short pattern);

public:
	static ShLineStyleComboList* GetInstance();

	QString GetLineStyleText(const ShLineStyle& lineStyle);
	QString GetLineStyleText(int index);
	inline int GetSize() const { return this->list.size(); }
	inline ShLineStyle GetLineStyle(int index) const { return this->list.at(index); }
	
	int Search(const ShLineStyle& lineStyle);
	int Search(unsigned short pattern);

};


#endif //_SHLINESTYLECOMBOLIST_H