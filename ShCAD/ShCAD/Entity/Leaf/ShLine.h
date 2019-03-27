


#ifndef _SHLINE_H
#define _SHLINE_H

#include "ShLeaf.h"

/* Class for Line entity */


class ShLine : public ShLeaf {

protected:
	ShLineData data;

public:
	ShLine();
	ShLine(const ShLineData &data);
	ShLine(const ShPropertyData& propertyData, const ShLineData &data, ShLayer *layer);
	ShLine(const ShLine& other);
	ShLine& operator=(const ShLine& other);
	~ShLine();

	ShLine* Clone();
	virtual void Accept(ShVisitor *shVisitor);
	virtual void Move(double cx, double cy);

	inline ShLineData GetData() const { return this->data; }
	void SetData(const ShLineData& data) { this->data = data; }

	ShPoint3d GetMid();
	inline ShPoint3d GetStart() const { return this->data.start; }
	inline ShPoint3d GetEnd() const { return this->data.end; }
	void SetStart(const ShPoint3d& start) { this->data.start = start; }
	void SetEnd(const ShPoint3d& end) { this->data.end = end; }
	

};


#endif //_SHLINE_H