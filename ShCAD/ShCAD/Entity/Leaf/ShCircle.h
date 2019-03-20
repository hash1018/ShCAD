

#ifndef _SHCIRCLE_H
#define _SHCIRCLE_H

#include "ShLeaf.h"

/* Class for Circle entity */

class ShCircle : public ShLeaf {
	
protected:
	ShCircleData data;

public:
	ShCircle();
	ShCircle(const ShCircleData& data);
	ShCircle(const ShPropertyData& propertyData, const ShCircleData &data, ShLayer *layer);
	ShCircle(const ShCircle& other);
	ShCircle& operator=(const ShCircle& other);
	~ShCircle();

	virtual ShCircle* Clone();
	virtual void Accept(ShVisitor *shVisitor);
	virtual void GetVertexPoint(VertexPoint vertexPoint, ShPoint3d &point);
	virtual void Move(double cx, double cy);

	virtual ShCircleData* CreateData();
	virtual void SetData(ShEntityData *data);

	inline ShCircleData GetData() const { return this->data; }
	void SetData(const ShCircleData& data) { this->data = data; }
	
	inline ShPoint3d GetCenter() const { return this->data.center; }
	inline double GetRadius() const { return this->data.radius; }
	void SetCenter(const ShPoint3d& center) { this->data.center = center; }
	void SetRadius(double radius) { this->data.radius = radius; }

};



#endif //_SHCIRCLE_H