

#include "ShObjectSnapCommandFactory.h"

ShObjectSnapCommandFactory::ShObjectSnapCommandFactory() {

}

ShObjectSnapCommandFactory::~ShObjectSnapCommandFactory() {

}

QString ShObjectSnapCommandFactory::create(ObjectSnap objectSnap) {

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
	else if (objectSnap == ObjectSnap::ObjectSnapIntersection)
		str = "_int of ";
	else if (objectSnap == ObjectSnap::ObjectSnapAppraentIntersection)
		str = "_appint of ";


	return str;
}