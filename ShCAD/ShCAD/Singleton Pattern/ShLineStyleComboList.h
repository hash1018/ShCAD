

#ifndef _SHLINESTYLECOMBOLIST_H
#define _SHLINESTYLECOMBOLIST_H

#include <qlist.h>
#include "ShPropertyData.h"

class ShLineStyleComboList {

private:
	ShLineStyle layerStyle; //only temporary
	ShLineStyle blockStyle; //only temporary
	QList<ShLineStyle> list;

private:
	ShLineStyleComboList();
	~ShLineStyleComboList();

	static ShLineStyleComboList instance;

	QString GetLineStyleShape(unsigned short pattern);

public:
	static ShLineStyleComboList* GetInstance();

	QString GetLayerLineStyleText();
	QString GetBlockLineStyleText();
	QString GetLineStyleText(int index);
	inline int GetSize() const { return this->list.size(); }

	ShLineStyle GetColorUsingComboBoxIndex(int comboBoxIndex);


};


#endif //_SHLINESTYLECOMBOLIST_H