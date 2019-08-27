
#ifndef _SHARC_H
#define _SHARC_H

#include "ShLeaf.h"

class ShArc : public ShLeaf {

protected:
	ShArcData data;

public:
	ShArc();
	ShArc(const ShPropertyData &propertyData, const ShArcData &data, ShLayer *layer);
	ShArc(const ShArcData &data);
	ShArc(const ShPoint3d &center, double radius, double startAngle, double endAngle);
	ShArc(const ShArc &other);
	~ShArc();

	ShArc& operator=(const ShArc &other);

	virtual ShArc* clone();
	virtual void accept(ShVisitor *visitor);

public:
	void setCenter(const ShPoint3d &center) { this->data.center = center; }
	void setRadius(double radius) { this->data.radius = radius; }
	void setStartAngle(double startAngle) { this->data.startAngle = startAngle; }
	void setEndAngle(double endAngle) { this->data.endAngle = endAngle; }
	void setData(const ShArcData &data) { this->data = data; }

public:
	inline const ShPoint3d& getCenter() const { return this->data.center; }
	inline double getRadius() const { return this->data.radius; }
	inline double getStartAngle() const { return this->data.startAngle; }
	inline double getEndAngle() const { return this->data.endAngle; }
	inline const ShArcData& getData() const { return this->data; }

	ShPoint3d getStart() const;
	ShPoint3d getEnd() const;
	ShPoint3d getMid() const;
};

#endif //_SHARC_H