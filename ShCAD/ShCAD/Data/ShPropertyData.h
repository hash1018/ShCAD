
#ifndef _SHPROPERTYDATA_H
#define _SHPROPERTYDATA_H

#include "Data\ShColor.h"

class ShPropertyData {

private:
	ShColor color;

public:
	ShPropertyData();
	ShPropertyData(const ShPropertyData &other);
	~ShPropertyData();

	ShPropertyData& operator=(const ShPropertyData &other);

	void setColor(const ShColor &color) { this->color = color; }

	inline ShColor getColor() const { return this->color; }

};

#endif //_SHPROPERTYDATA_H