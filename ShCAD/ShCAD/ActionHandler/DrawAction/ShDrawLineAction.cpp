

#include "ShDrawLineAction.h"
#include <QMouseEvent>
#include "KeyHandler\ShKeyHandler.h"
#include "KeyHandler\ShCustomKey.h"
#include "Entity\Private\ShFootOfPerpendicularVisitor.h"

ShDrawLineAction::ShDrawLineAction(ShCADWidget *widget)
	:ShDrawAction(widget), status(PickedNothing), subAction(Default) {

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowKey(KeyType::Enter).
		allowKey(KeyType::Return).
		allowKey(KeyType::EscCancelCurrent).
		allowInput().
		allowCustom(new ShCustomKey<ShDrawLineAction>(Qt::Key::Key_I, Qt::KeyboardModifier::ControlModifier, this, &ShDrawLineAction::temp)).
		build();

	this->subDrawLineAction = new ShSubDrawLineAction_Default(this, this->widget);
}

ShDrawLineAction::~ShDrawLineAction() {

	if (this->subDrawLineAction != nullptr)
		delete this->subDrawLineAction;
}

void ShDrawLineAction::mouseLeftPressEvent(ShActionData &data) {

	this->subDrawLineAction->mouseLeftPressEvent(data);
}

void ShDrawLineAction::mouseMoveEvent(ShActionData &data) {

	this->subDrawLineAction->mouseMoveEvent(data);
}


ActionType ShDrawLineAction::getType() {

	return ActionType::ActionDrawLine;
}

QString ShDrawLineAction::getHeadTitle() {

	QString text;

	if (this->status == Status::PickedNothing)
		text = "Line >> " + shGetLanValue_command("Command/Specify first point") + ": ";
	else
		text = "Line >> " + shGetLanValue_command("Command/Specify next point") + ": ";

	return text;
}

ShAvailableDraft ShDrawLineAction::getAvailableDraft() {
	
	ShAvailableDraft draft;

	if (this->status == Status::PickedNothing) {
		draft.setAvailableOrthogonal(true);
		draft.setAvailableSnap(true);
		ShPoint3d mouse = this->widget->getMousePoint();
		draft.setOrthogonalBasePoint(mouse);
		draft.setSnapBasePoint(mouse);
	}
	else {
	
		ShLine *prevLine = dynamic_cast<ShLine*>((*this->widget->getPreview().begin()));

		if (this->subAction == SubAction::Default) {
			draft.setAvailableOrthogonal(true);
			draft.setOrthogonalBasePoint(prevLine->getStart());
		}

		draft.setAvailableSnap(true);
		draft.setSnapBasePoint(prevLine->getStart());
	}

	return draft;
}

void ShDrawLineAction::invalidate(ShPoint3d &point) {
	
	this->subDrawLineAction->invalidate(point);
}

void ShDrawLineAction::changeSubAction(SubAction subAction) {

	if (this->subDrawLineAction != nullptr)
		delete this->subDrawLineAction;

	this->subAction = subAction;

	if (subAction == SubAction::Default)
		this->subDrawLineAction = new ShSubDrawLineAction_Default(this, this->widget);
	else
		this->subDrawLineAction = new ShSubDrawLineAction_Perpendicular(this, this->widget);

}


#include <qmessagebox.h>
void ShDrawLineAction::temp() {

	QMessageBox box;
	box.setText("Tem");
	box.exec();
}



////////////////////////////////////////////////////////////////////////////////////////

ShSubDrawLineAction::ShSubDrawLineAction(ShDrawLineAction *drawLineAction, ShCADWidget *widget)
	:drawLineAction(drawLineAction), widget(widget) {

}

ShSubDrawLineAction::~ShSubDrawLineAction() {

}

ShDrawLineAction::Status& ShSubDrawLineAction::getStatus() {

	return this->drawLineAction->status;
}

void ShSubDrawLineAction::addEntity(ShEntity *newEntity, const QString &type) {

	this->drawLineAction->addEntity(newEntity, type);
}

void ShSubDrawLineAction::triggerSucceeded() {

	this->drawLineAction->triggerSucceeded();
}

//////////////////////////////////////////////////////////////////////////////////////////


ShSubDrawLineAction_Default::ShSubDrawLineAction_Default(ShDrawLineAction *drawLineAction, ShCADWidget *widget)
	:ShSubDrawLineAction(drawLineAction, widget) {

}

ShSubDrawLineAction_Default::~ShSubDrawLineAction_Default() {

}

void ShSubDrawLineAction_Default::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShSubDrawLineAction_Default::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

void ShSubDrawLineAction_Default::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawLineAction::PickedNothing) {

		this->getStatus() = ShDrawLineAction::PickedStart;

		this->widget->getPreview().add(new ShLine(this->widget->getPropertyData(), ShLineData(point, point), this->widget->getCurrentLayer()));

		this->triggerSucceeded();
	}
	else if (this->getStatus() == ShDrawLineAction::PickedStart) {

		ShLine *preview = dynamic_cast<ShLine*>((*this->widget->getPreview().begin()));
		ShLineData data = preview->getData();
		data.end = point;

		preview->setData(data);

		this->addEntity(preview->clone(), "Line");

		data = ShLineData(point, point);
		preview->setData(data);

		this->triggerSucceeded();
	}

}

void ShSubDrawLineAction_Default::invalidate(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawLineAction::PickedStart) {

		ShLine *prevLine = dynamic_cast<ShLine*>((*this->widget->getPreview().begin()));
		prevLine->setEnd(point);
		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}

///////////////////////////////////////////////////////////////////////////////////////////

ShSubDrawLineAction_Perpendicular::ShSubDrawLineAction_Perpendicular(ShDrawLineAction *drawLineAction, ShCADWidget *widget)
	:ShSubDrawLineAction(drawLineAction, widget) {

}

ShSubDrawLineAction_Perpendicular::~ShSubDrawLineAction_Perpendicular() {

}

void ShSubDrawLineAction_Perpendicular::mouseLeftPressEvent(ShActionData &data) {

	this->trigger(data.point);
}

void ShSubDrawLineAction_Perpendicular::mouseMoveEvent(ShActionData &data) {

	this->invalidate(data.point);
}

void ShSubDrawLineAction_Perpendicular::trigger(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawLineAction::PickedStart) {

		ShLine *prevLine = dynamic_cast<ShLine*>((*this->widget->getPreview().begin()));

		ShPoint3d perpendicular;

		ShFootOfPerpendicularVisitor visitor(perpendicular.x, perpendicular.y, point);
		this->perpendicularBase->accept(&visitor);

		prevLine->setStart(perpendicular);
		prevLine->setEnd(point);

		this->addEntity(prevLine->clone(), "Line");

		prevLine->setStart(point);
		prevLine->setEnd(point);

		this->triggerSucceeded();

		this->drawLineAction->changeSubAction(ShDrawLineAction::SubAction::Default);
	}
}

void ShSubDrawLineAction_Perpendicular::invalidate(const ShPoint3d &point) {

	if (this->getStatus() == ShDrawLineAction::PickedStart) {

		ShLine *prevLine = dynamic_cast<ShLine*>((*this->widget->getPreview().begin()));

		ShPoint3d perpendicular;

		ShFootOfPerpendicularVisitor visitor(perpendicular.x, perpendicular.y, point);
		this->perpendicularBase->accept(&visitor);

		prevLine->setStart(perpendicular);
		prevLine->setEnd(point);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}