

#ifndef _SHCOLORCOMBOLIST_H
#define _SHCOLORCOMBOLIST_H

#include <qlist.h>
#include "ShPropertyData.h"
#include <qpixmap.h>


class ShColorComboList {


private:
	ShColor layerColor; //only temporary.
	ShColor blockColor; //only temporary.
	QList<ShColor> list;
	

private:
	ShColorComboList();
	~ShColorComboList();

	static ShColorComboList instance;

public:
	static ShColorComboList* GetInstance();


	QPixmap GetLayerColorImage(int width, int height);
	QPixmap GetBlockColorImage(int width, int height);
	QPixmap GetColorImage(int width, int height,int index);
	QString GetLayerColorText();
	QString GetBlockColorText();
	QString GetColorText(int index);

	int Search(const ShColor& color);
	void Add(const ShColor& color);

	ShColor GetColorUsingComboBoxIndex(int comboBoxIndex);

	inline int GetSize() const { return this->list.size(); }
	inline ShColor GetColor(int index) const { return this->list.at(index); }
	inline ShColor GetLayerColor() const { return this->layerColor; }
	inline ShColor GetBlockColor() const { return this->blockColor; }

};

#endif //_SHCOLORCOMBOLIST_H