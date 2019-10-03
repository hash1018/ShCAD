
#ifndef _SHPOINT_H
#define _SHPOINT_H

#include "Entity\Leaf\ShLeaf.h"

class ShPointStyle;

class ShPoint : public ShLeaf {

protected:
	ShPoint3d position;
	const ShPointStyle *pointStyle;

public:
	ShPoint();
	ShPoint(const ShPoint3d &position, const ShPropertyData &propertyData, ShLayer *layer, const ShPointStyle *pointStyle);
	ShPoint(const ShPoint &other);
	~ShPoint();

	ShPoint& operator=(const ShPoint &other);

	virtual ShPoint* clone();
	virtual void accept(ShVisitor *visitor);

public:
	void setPosition(const ShPoint3d &position) { this->position = position; }
	inline const ShPoint3d& getPosition() const { return this->position; }
	inline const ShPointStyle* const getPointStyle() const { return this->pointStyle; }
};

#endif //_SHPOINT_H