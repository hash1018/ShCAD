

#ifndef _SHARC_H
#define _SHARC_H

#include "ShLeaf.h"

/* Class for Arc entity */

class ShArc : public ShLeaf {

protected:
	ShArcData data;

public:
	ShArc();
	ShArc(const ShArcData& data);
	ShArc(const ShPropertyData& propertyData, const ShArcData &data, ShLayer *layer);
	ShArc(const ShArc& other);
	ShArc& operator=(const ShArc& other);
	~ShArc();

	ShArc* Clone();
	virtual void Accept(ShVisitor *shVisitor);
	virtual void GetVertexPoint(VertexPoint vertexPoint, ShPoint3d &point);
	virtual void Move(double cx, double cy);
	virtual ShArcData* CreateData();
	virtual void SetData(ShEntityData *data);

	inline ShArcData GetData() const { return this->data; }
	void SetData(const ShArcData& data) { this->data = data; }

	inline ShPoint3d GetCenter() const { return this->data.center; }
	inline double GetRadius() const { return this->data.radius; }
	inline double GetStartAngle() const { return this->data.startAngle; }
	inline double GetEndAngle() const { return this->data.endAngle; }
	void SetCenter(const ShPoint3d& center) { this->data.center = center; }
	void SetRadius(double radius) { this->data.radius = radius; }
	void SetStartAngle(double startAngle) { this->data.startAngle = startAngle; }
	void SetEndAngle(double endAngle) { this->data.endAngle = endAngle; }

	ShPoint3d GetStart();
	ShPoint3d GetEnd();
	ShPoint3d GetMid();
};


#endif //_SHARC_H