
#include "ShModifyMoveAction.h"
#include <qpainter.h>
#include "Manager\ShLanguageManager.h"

ShModifyMoveAction::ShModifyMoveAction(ShCADWidget *widget)
	:ShModifyAction(widget), status(Status::SelectingEntities) {


}

ShModifyMoveAction::~ShModifyMoveAction() {

}

void ShModifyMoveAction::mouseLeftPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {
		this->triggerSelectingEntities(data.mouseEvent);
	}
	else if (this->status == Status::FinishedSelectingEntities) {
	
	}
	else if (this->status == Status::PickedBasePoint) {
	
	}


}

void ShModifyMoveAction::mouseRightPressEvent(ShActionData &data) {

	if (this->status == Status::SelectingEntities) {
	
	}

}

void ShModifyMoveAction::mouseMoveEvent(ShActionData &data) {

	if (this->status == Status::PickedBasePoint) {
	

	}
}

ActionType ShModifyMoveAction::getType() {

	return ActionType::ActionModifyMove;
}

QString ShModifyMoveAction::getHeadTitle() {

	QString text;

	if (this->status == Status::SelectingEntities) {
		text = "Move >> " + shGetLanValue_command("Command/Select objects") + ": ";
	}
	else if (this->status == Status::FinishedSelectingEntities) {
		text = "Move >> " + shGetLanValue_command("Command/Specify base point") + ": ";
	}
	else if (this->status == Status::PickedBasePoint) {
		text = "Move >> " + shGetLanValue_command("Command/Specify second point") + ": ";
	}

	return text;
}

ShAvailableDraft ShModifyMoveAction::getAvailableDraft() {
	
	ShAvailableDraft draft;

	if (this->status == Status::FinishedSelectingEntities) {
	
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->widget->getMousePoint());
		draft.setSnapBasePoint(this->widget->getMousePoint());
	}
	else if (this->status == Status::PickedBasePoint) {
	
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		draft.setOrthogonalBasePoint(this->widget->getRubberBand().getStart());
		draft.setSnapBasePoint(this->widget->getRubberBand().getStart());
	}

	return draft;
}

void ShModifyMoveAction::invalidate(ShPoint3d point) {

}

QCursor ShModifyMoveAction::getCursorShape() {

	if (this->status == Status::SelectingEntities) {
		QPixmap pix(32, 32);
		pix.fill(Qt::transparent); // Otherwise you get a black background :(
		QPainter painter(&pix);
		painter.setPen(QColor(255, 255, 255));
		painter.drawRect(13, 13, 6, 6);

		return QCursor(pix);
	}

	return QCursor(Qt::CursorShape::CrossCursor);
}