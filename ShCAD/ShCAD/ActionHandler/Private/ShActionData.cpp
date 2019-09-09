
#include "ShActionData.h"

ShActionData::ShActionData()
	:mouseEvent(nullptr), keyEvent(nullptr) {

}

ShActionData::~ShActionData() {

}

/////////////////////////////////////////

ShDecoratorActionData::ShDecoratorActionData()
	:snapAccepted(true), orthAccepted(true) {

}

ShDecoratorActionData::~ShDecoratorActionData() {

}