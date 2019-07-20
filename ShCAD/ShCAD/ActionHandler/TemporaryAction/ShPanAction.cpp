
#include "ShPanAction.h"
#include <QMouseEvent>
#include "UnRedo\ShPanTransaction.h"
#include "Base\ShGlobal.h"
#include "Manager\ShLanguageManager.h"

ShPanAction::ShPanAction(ShCADWidget *widget)
	:ShTemporaryAction(widget) {

}

ShPanAction::~ShPanAction() {

}

void ShPanAction::mouseMidPressEvent(ShActionData &data) {

	
	int dx = data.mouseEvent->x();
	int dy = data.mouseEvent->y();
	this->prevX = dx;
	this->prevY = dy;

	ShPoint3d coordinate = data.point;

	
	ShGlobal::pushNewTransaction(this->widget, new ShPanTransaction(this->widget, coordinate, dx, dy));
	
}

void ShPanAction::mouseMoveEvent(ShActionData &data) {
	
	double hPos = this->widget->getScrollPosition().horizontal;
	double vPos = this->widget->getScrollPosition().vertical;
	hPos += this->prevX - data.mouseEvent->x();
	vPos += this->prevY - data.mouseEvent->y();

	this->widget->setScrollPosition(ShScrollPosition(vPos, hPos));

	this->prevX = data.mouseEvent->x();
	this->prevY = data.mouseEvent->y();

	this->widget->update(DrawType::DrawAll);
}

void ShPanAction::mouseReleaseEvent(ShActionData &data) {
	
	if (data.mouseEvent->button() & Qt::MouseButton::MiddleButton) {

		this->widget->captureImage();
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}

	this->returnToPrevious();

}

ActionType ShPanAction::getType() {

	return ActionType::ActionTempPan;
}

QCursor ShPanAction::getCursorShape() {

	return QCursor(Qt::ClosedHandCursor);
}

QString ShPanAction::getHeadTitle() {

	return shGetLanValue_command("Command/Command");
}