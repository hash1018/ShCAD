
#include "ShDisposableExtensionSnapAction.h"

ShDisposableExtensionSnapAction::ShDisposableExtensionSnapAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, child) {

}

ShDisposableExtensionSnapAction::~ShDisposableExtensionSnapAction() {

}

void ShDisposableExtensionSnapAction::mouseLeftPressEvent(ShActionData &data) {

}

void ShDisposableExtensionSnapAction::mouseMoveEvent(ShActionData &data) {

}

void ShDisposableExtensionSnapAction::draw(QPainter *painter) {

}

void ShDisposableExtensionSnapAction::invalidate(ShDecoratorActionData &data) {

}

bool ShDisposableExtensionSnapAction::search(const ShPoint3d &point) {

	return false;
}