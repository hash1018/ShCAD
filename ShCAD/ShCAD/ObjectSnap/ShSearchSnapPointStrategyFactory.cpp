
#include "ShSearchSnapPointStrategyFactory.h"
#include "ShSearchSnapPointStrategy.h"

ShSearchSnapPointStrategyFactory::ShSearchSnapPointStrategyFactory() {

}

ShSearchSnapPointStrategyFactory::~ShSearchSnapPointStrategyFactory() {

}

ShSearchSnapPointStrategy* ShSearchSnapPointStrategyFactory::create(ObjectSnap objectSnap, ShCADWidget *widget) {

	if (objectSnap == ObjectSnap::ObjectSnapEndPoint)
		return new ShSearchSnapPointStrategy_End(widget);
	else if (objectSnap == ObjectSnap::ObjectSnapMidPoint)
		return new ShSearchSnapPointStrategy_Mid(widget);
	else if (objectSnap == ObjectSnap::ObjectSnapPerpendicular)
		return new ShSearchSnapPointStrategy_Perpendicular(widget);
	else if (objectSnap == ObjectSnap::ObjectSnapCenter)
		return new ShSearchSnapPointStrategy_Center(widget);
	else if (objectSnap == ObjectSnap::ObjectSnapQuadrant)
		return new ShSearchSnapPointStrategy_Quadrant(widget);
	else if (objectSnap == ObjectSnap::ObjectSnapIntersection)
		return new ShSearchSnapPointStrategy_Intersecion(widget);


	return new ShSearchSnapPointStrategy_Nothing(widget);
}