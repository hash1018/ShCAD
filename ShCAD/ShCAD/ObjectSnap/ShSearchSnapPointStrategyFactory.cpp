
#include "ShSearchSnapPointStrategyFactory.h"
#include "ShSearchSnapPointStrategy.h"

ShSearchSnapPointStrategyFactory::ShSearchSnapPointStrategyFactory() {

}

ShSearchSnapPointStrategyFactory::~ShSearchSnapPointStrategyFactory() {

}

ShSearchSnapPointStrategy* ShSearchSnapPointStrategyFactory::create(ObjectSnap objectSnap, ShCADWidget *widget) {

	if (objectSnap == ObjectSnap::ObjectSnapEndPoint)
		return new ShSearchSnapPointStrategy_End(widget);

	//else if (objectSnap == ObjectSnap::ObjectSnapMidPoint)
	//	new ShObjectSnapStrategy_MidPoint(view);
	//else if (objectSnap == ObjectSnap::ObjectSnapPerpendicular)
	//	return new ShObjectSnapStrategy_Perpendicular(view);
	//else if (objectSnap == ObjectSnap::ObjectSnapCenter)
	//	return new ShObjectSnapStrategy_Center(view);
	//else if (objectSnap == ObjectSnap::ObjectSnapQuadrant)
	//	return new ShObjectSnapStrategy_Quadrant(view);


	//return new ShObjectSnapStrategy_Nothing(view);


	return new ShSearchSnapPointStrategy_Nothing(widget);
}