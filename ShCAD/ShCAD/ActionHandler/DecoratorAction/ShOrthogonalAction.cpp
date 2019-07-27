
#include "ShOrthogonalAction.h"
#include "Base\ShMath.h"

ShOrthogonalAction::ShOrthogonalAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShDecoratorAction(widget, actionHandler, child) {

}

ShOrthogonalAction::~ShOrthogonalAction() {


}

void ShOrthogonalAction::mouseLeftPressEvent(ShActionData &data) {



}

void ShOrthogonalAction::mouseMoveEvent(ShActionData &data) {

}

void ShOrthogonalAction::getOrthogonalPoint(double x, double y, double mouseX, double mouseY, double &orthX, double &orthY) {

	double disVertical, disHorizontal;

	disVertical = math::getDistance(x, y, x, mouseY);
	disHorizontal = math::getDistance(x, y, mouseX, y);

	if (math::compare(disVertical, disHorizontal) == 1) {

		orthX = x;
		orthY = mouseY;
	}
	else {

		orthX = mouseX;
		orthY = y;
	}
}