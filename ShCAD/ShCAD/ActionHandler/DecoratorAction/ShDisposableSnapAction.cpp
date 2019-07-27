
#include "ShDisposableSnapAction.h"

ShDisposableSnapAction::ShDisposableSnapAction(ShCADWidget *widget, ShActionHandler *actionHandler, ObjectSnap objectSnap, ShDecoratorAction *child)
	:ShDecoratorAction(widget, actionHandler, child) {

}

ShDisposableSnapAction::~ShDisposableSnapAction() {

	
}

void ShDisposableSnapAction::keyPressEvent(ShActionData &data) {

}

void ShDisposableSnapAction::draw(QPainter *painter) {


}

void ShDisposableSnapAction::invalidate(ShPoint3d point) {


}

/////////////////////////////////////////////////////////////////

ShDisposableSnapAction_General::ShDisposableSnapAction_General(ShCADWidget *widget, ShActionHandler *actionHandler, ObjectSnap objectSnap, ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, objectSnap, child) {

}


ShDisposableSnapAction_General::~ShDisposableSnapAction_General() {


}

void ShDisposableSnapAction_General::mouseLeftPressEvent(ShActionData &data) {


}

void ShDisposableSnapAction_General::mouseMoveEvent(ShActionData &data) {


}