
#include "ShOrthogonalAction.h"
#include "Base\ShMath.h"

ShOrthogonalAction::ShOrthogonalAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShDecoratorAction(widget, actionHandler, child) {

}

ShOrthogonalAction::~ShOrthogonalAction() {


}

void ShOrthogonalAction::mouseLeftPressEvent(ShActionData &data) {

	
	ShAvailableDraft availableDraft = this->actionHandler->getAvailableDraft();

	if (availableDraft.getAvailableOrthogonal() == true) {
	
		ShPoint3d basePoint, orth;
		ShPoint3d mouse = this->widget->getMousePoint();

		if (dynamic_cast<ShDecoratorActionData&>(data).snapAccepted == false) {

			basePoint = availableDraft.getOrthogonalBasePoint();
			this->getOrthogonalPoint(basePoint.x, basePoint.y, mouse.x, mouse.y, orth.x, orth.y);
			data.point = orth;
		}
		
	}

	ShDecoratorAction::mouseLeftPressEvent(data);
}

void ShOrthogonalAction::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft availableDraft = this->actionHandler->getAvailableDraft();

	if (availableDraft.getAvailableOrthogonal() == true) {

		ShPoint3d basePoint, orth;
		ShPoint3d mouse = this->widget->getMousePoint();

		basePoint = availableDraft.getOrthogonalBasePoint();
		this->getOrthogonalPoint(basePoint.x, basePoint.y, mouse.x, mouse.y, orth.x, orth.y);
		data.point = orth;
	}

	ShDecoratorAction::mouseMoveEvent(data);
}

void ShOrthogonalAction::invalidate(ShPoint3d &point) {

	ShAvailableDraft availableDraft = this->actionHandler->getAvailableDraft();

	if (availableDraft.getAvailableOrthogonal() == true) {

		ShPoint3d basePoint, orth;
		ShPoint3d mouse = this->widget->getMousePoint();

		basePoint = availableDraft.getOrthogonalBasePoint();
		this->getOrthogonalPoint(basePoint.x, basePoint.y, mouse.x, mouse.y, orth.x, orth.y);
		point = orth;

	}

	ShDecoratorAction::invalidate(point);
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