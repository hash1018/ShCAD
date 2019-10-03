
#include "ShPointStyle.h"
#include "Entity\Leaf\ShDot.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShPoint.h"

ShPointStyle::ShPointStyle()
	:shape(PointShape::Dot), pointSize(5.0), sizeType(RelativeToScreen) {

}

ShPointStyle::~ShPointStyle() {

}


void ShPointStyle::getComponentDependsOnStyle(QList<ShEntity*> &components, const ShPoint3d &position, PointShape shape, double pointSize, SizeType sizeType) {

	if (shape == PointShape::Dot) {
	
		components.append(new ShDot(position));
	}
}

void ShPointStyle::getComponentDependsOnStyle(QList<ShEntity*> &components, ShPoint *point) {

	ShPointStyle::getComponentDependsOnStyle(components, point->getPosition(), point->getPointStyle()->getShape(),
		point->getPointStyle()->getPointSize(), point->getPointStyle()->getSizeType());
}