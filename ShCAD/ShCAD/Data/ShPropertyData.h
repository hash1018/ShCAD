
#ifndef _SHPROPERTYDATA_H
#define _SHPROPERTYDATA_H

#include "Data\ShColor.h"
#include "Data\ShLineStyle.h"

class ShPropertyData {

private:
	ShColor color;
	ShLineStyle lineStyle;

public:
	ShPropertyData();
	ShPropertyData(const ShPropertyData &other);
	~ShPropertyData();

	ShPropertyData& operator=(const ShPropertyData &other);

	void setColor(const ShColor &color) { this->color = color; }
	void setLineStyle(const ShLineStyle &lineStyle) { this->lineStyle = lineStyle; }

	inline const ShColor& getColor() const { return this->color; }
	inline const ShLineStyle& getLineStyle() const { return this->lineStyle; }

};

#endif //_SHPROPERTYDATA_H