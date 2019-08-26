
#ifndef _SHLINE_H
#define _SHLINE_H

#include "ShLeaf.h"

class ShLine : public ShLeaf {

protected:
	ShLineData data;

public:
	ShLine();
	ShLine(const ShPropertyData &propertyData, const ShLineData &data, ShLayer *layer);
	ShLine(const ShLineData &data);
	ShLine(const ShPoint3d &start, const ShPoint3d &end);
	ShLine(const ShLine &other);
	~ShLine();
	ShLine& operator=(const ShLine &other);

	virtual ShLine* clone();
	virtual void accept(ShVisitor *visitor);

public:
	virtual void setData(const ShLineData &data) { this->data = data; }
	void setStart(const ShPoint3d &start) { this->data.start = start; }
	virtual void setEnd(const ShPoint3d &end) { this->data.end = end; }

public:
	virtual const ShLineData& getData() const { return this->data; }
	virtual const ShPoint3d& getStart() const { return this->data.start; }
	virtual const ShPoint3d& getEnd() const { return this->data.end; }

	virtual ShPoint3d getMid();
};

#endif //_SHLINE_H