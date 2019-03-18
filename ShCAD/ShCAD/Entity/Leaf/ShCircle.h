

#ifndef _SHCIRCLE_H
#define _SHCIRCLE_H

#include "ShLeaf.h"
#include "ShPoint.h"

class ShCircleData {

public:
	ShPoint3d center;
	double radius;
	
	ShCircleData();
	ShCircleData(ShPoint3d& center, double radius);
	ShCircleData(const ShCircleData& data);
	bool operator==(const ShCircleData& data);
	ShCircleData& operator=(const ShCircleData &data);

};

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
	virtual void GetHitPoint(HitPoint hitPoint, ShPoint3d &point);
	virtual void Move(double cx, double cy);

	inline ShCircleData GetData() const { return this->data; }
	void SetData(const ShCircleData& data) { this->data = data; }
	
	inline ShPoint3d GetCenter() const { return this->data.center; }
	inline double GetRadius() const { return this->data.radius; }
	void SetCenter(const ShPoint3d& center) { this->data.center = center; }
	void SetRadius(double radius) { this->data.radius = radius; }

};



#endif //_SHCIRCLE_H