
#ifndef _SHDOT_H
#define _SHDOT_H

#include "Entity\Leaf\ShLeaf.h"

class ShDot : public ShLeaf {

protected:
	ShPoint3d position;

public:
	ShDot();
	ShDot(const ShPoint3d &position);
	ShDot(const ShPoint3d &position, const ShPropertyData &propertyData, ShLayer *layer);
	ShDot(const ShDot &other);
	~ShDot();

	ShDot& operator=(const ShDot &other);

	virtual ShDot* clone();
	virtual void accept(ShVisitor *visitor);

public:
	void setPosition(const ShPoint3d &position) { this->position = position; }
	inline const ShPoint3d& getPosition() const { return this->position; }

};

#endif //_SHDOT_H