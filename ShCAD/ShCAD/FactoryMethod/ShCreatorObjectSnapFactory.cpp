

#include "ShCreatorObjectSnapFactory.h"
#include "ShObjectSnapState.h"

ShCreatorObjectSnapFactory::ShCreatorObjectSnapFactory() {

}

ShCreatorObjectSnapFactory::~ShCreatorObjectSnapFactory() {

}

ShObjectSnapState* ShCreatorObjectSnapFactory::Create(ObjectSnap objectSnap, ShGraphicView *view) {


	if (objectSnap == ObjectSnap::ObjectSnapEndPoint)
		return new ShObjectSnapState_EndPoint(view);
	else if (objectSnap == ObjectSnap::ObjectSnapMidPoint)
		return new ShObjectSnapState_MidPoint(view);

	return new ShObjectSnapState_Nothing(view);
}