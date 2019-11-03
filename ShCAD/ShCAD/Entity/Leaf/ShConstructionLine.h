
#ifndef _SHCONSTRUCTIONLINE_H
#define _SHCONSTRUCTIONLINE_H

#include "ShLine.h"

class ShConstructionLine : public ShLine {

public:
	ShConstructionLine();
	ShConstructionLine(const ShPropertyData &propertyData, const ShLineData &data, ShLayer *layer);
	ShConstructionLine(const ShLineData &data);
	ShConstructionLine(const ShPoint3d &start, const ShPoint3d &end);
	ShConstructionLine(const ShConstructionLine &other);
	~ShConstructionLine();
	ShConstructionLine& operator=(const ShConstructionLine &other);

	virtual ShConstructionLine* clone();
	virtual void accept(ShVisitor *visitor);
};

#endif //_SHCONSTRUCTIONLINE_H