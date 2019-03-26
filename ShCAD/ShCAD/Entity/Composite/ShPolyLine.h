
#ifndef _SHPOLYLINE_H
#define _SHPOLYLINE_H

#include "ShComposite.h"

class ShPolyLine : public ShComposite {

public:
	ShPolyLine(const ShPropertyData &propertyData, ShLayer *layer);
	ShPolyLine(const ShPolyLine& other);
	~ShPolyLine();
	ShPolyLine& operator=(const ShPolyLine& other);

	virtual ShPolyLine* Clone();
	virtual void Accept(ShVisitor *visitor);
	virtual void Move(double cx, double cy);

	virtual ShPolyLineData* CreateData();
	virtual void SetData(ShEntityData *data);

protected:
	virtual void Select();
	virtual void UnSelect();

};

#endif //_SHPOLYLINE_H