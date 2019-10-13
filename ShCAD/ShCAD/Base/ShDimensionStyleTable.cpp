
#include "ShDimensionStyleTable.h"
#include "ShDimensionStyle.h"

ShDimensionStyleTable::ShDimensionStyleTable() {

	ShDimensionStyle *dimensionStyle = new ShDimensionStyle("Standard");
	this->styles.append(dimensionStyle);
	this->currentStyle = dimensionStyle;
}

ShDimensionStyleTable::~ShDimensionStyleTable() {

	for (int i = 0; i < this->styles.size(); i++)
		delete this->styles.at(i);
}