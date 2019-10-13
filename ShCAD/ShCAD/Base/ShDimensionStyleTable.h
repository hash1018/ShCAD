
#ifndef _SHDIMENSIONSTYLETABLE_H
#define _SHDIMENSIONSTYLETABLE_H

#include <qlist.h>

class ShDimensionStyle;
class ShDimensionStyleTable {

private:
	QList<ShDimensionStyle*> styles;
	ShDimensionStyle *currentStyle;

public:
	ShDimensionStyleTable();
	~ShDimensionStyleTable();

public:
	void setCurrentStyle(int index) { this->currentStyle = this->styles.at(index); }
	void setCurrentStyle(ShDimensionStyle *dimensionStyle) { this->currentStyle = dimensionStyle; }

public:
	inline ShDimensionStyle* getCurrentStyle() const { return this->currentStyle; }
	inline ShDimensionStyle* getDimensionStyle(int index) { this->styles.at(index); }
};

#endif //_SHDIMENSIONSTYLETABLE_H