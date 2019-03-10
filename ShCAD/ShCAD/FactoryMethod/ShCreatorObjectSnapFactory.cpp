

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
	else if (objectSnap == ObjectSnap::ObjectSnapCenter)
		return new ShObjectSnapStrategy_Center(view);
	else if (objectSnap == ObjectSnap::ObjectSnapQuadrant)
		return new ShObjectSnapStrategy_Quadrant(view);


	return new ShObjectSnapStrategy_Nothing(view);
}


ShCreatorObjectSnapCommandFactory::ShCreatorObjectSnapCommandFactory() {

}

ShCreatorObjectSnapCommandFactory::~ShCreatorObjectSnapCommandFactory() {

}

QString ShCreatorObjectSnapCommandFactory::Create(ObjectSnap objectSnap) {

	QString str = "";

	if (objectSnap == ObjectSnap::ObjectSnapEndPoint)
		str = "_end point ";
	else if (objectSnap == ObjectSnap::ObjectSnapMidPoint)
		str = "_mid point ";
	else if (objectSnap == ObjectSnap::ObjectSnapPerpendicular)
		str = "_perpendicular to ";
	else if (objectSnap == ObjectSnap::ObjectSnapCenter)
		str = "_center ";
	else if (objectSnap == ObjectSnap::ObjectSnapQuadrant)
		str = "_quadrant ";


	return str;
}
