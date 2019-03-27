
#ifndef _SHPOLYLINE_H
#define _SHPOLYLINE_H

#include "ShComposite.h"

class ShPolyLine : public ShComposite {


private:
	ShPolyLineData data;

public:
	ShPolyLine(const ShPropertyData &propertyData, ShLayer *layer);
	ShPolyLine(const ShPolyLine& other);
	~ShPolyLine();
	ShPolyLine& operator=(const ShPolyLine& other);

	

	virtual ShPolyLine* Clone();
	virtual void Accept(ShVisitor *visitor);
	virtual void Move(double cx, double cy);

	virtual void SetLayer(ShLayer *layer);
	virtual void SetPropertyData(const ShPropertyData& data);

	void SetData(const ShPolyLineData& data) { this->data = data; }
	inline ShPolyLineData GetData() const { return this->data; }

	void SetStart(const ShPoint3d& start) { this->data.start = start; }
	void SetEnd(const ShPoint3d& end) { this->data.end = end;}

protected:
	virtual void Select();
	virtual void UnSelect();

};

#endif //_SHPOLYLINE_H