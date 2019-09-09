
#include "ShLastBasePoint.h"

ShLastBasePoint ShLastBasePoint::instance;

ShLastBasePoint::ShLastBasePoint() {

}

ShLastBasePoint::~ShLastBasePoint() {

}

ShLastBasePoint* ShLastBasePoint::getInstance() {

	return &(ShLastBasePoint::instance);
}