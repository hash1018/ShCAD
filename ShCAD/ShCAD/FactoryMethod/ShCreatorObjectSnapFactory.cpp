

#include "ShCreatorObjectSnapFactory.h"
#include "Strategy Pattern\ShObjectSnapStrategy.h"

ShCreatorObjectSnapFactory::ShCreatorObjectSnapFactory() {

}

ShCreatorObjectSnapFactory::~ShCreatorObjectSnapFactory() {

}

ShObjectSnapStrategy* ShCreatorObjectSnapFactory::Create(ObjectSnap objectSnap, ShGraphicView *view) {


	if (objectSnap == ObjectSnap::ObjectSnapEndPoint)
		return new ShObjectSnapStrategy_EndPoint(view);
	else if (objectSnap == ObjectSnap::ObjectSnapMidPoint)
		return new ShObjectSnapStrategy_MidPoint(view);
	else if (objectSnap == ObjectSnap::ObjectSnapPerpendicular)
		return new ShObjectSnapStrategy_Perpendicular(view);


	return new ShObjectSnapStrategy_Nothing(view);
}