
#include "ShActionData.h"

ShActionData::ShActionData()
	:mouseEvent(nullptr), keyEvent(nullptr) {

}

ShActionData::~ShActionData() {

}

/////////////////////////////////////////

ShDecoratorActionData::ShDecoratorActionData()
	:snapAccepted(false) {

}

ShDecoratorActionData::~ShDecoratorActionData() {

}