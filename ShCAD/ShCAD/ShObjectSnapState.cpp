

#include "ShObjectSnapState.h"

ShObjectSnapState::ShObjectSnapState() {

}

ShObjectSnapState::~ShObjectSnapState() {

}

//////////////////////////////////////////////////////////////////////////


ShObjectSnapState_Nothing::ShObjectSnapState_Nothing() {

}

ShObjectSnapState_Nothing::~ShObjectSnapState_Nothing() {

}


void ShObjectSnapState_Nothing::MousePressEvent(QMouseEvent *event) {

}

void ShObjectSnapState_Nothing::MouseMoveEvent(QMouseEvent *event) {


}

///////////////////////////////////////////////////////////////////////////

ShObjectSnapState_EndPoint::ShObjectSnapState_EndPoint() {

}

ShObjectSnapState_EndPoint::~ShObjectSnapState_EndPoint() {

}

void ShObjectSnapState_EndPoint::MousePressEvent(QMouseEvent *event) {

}

void ShObjectSnapState_EndPoint::MouseMoveEvent(QMouseEvent *event) {




}