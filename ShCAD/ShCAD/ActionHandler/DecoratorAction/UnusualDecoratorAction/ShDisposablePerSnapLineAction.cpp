
#include "ShDisposablePerSnapLineAction.h"
#include "ActionHandler\DrawAction\ShDrawLineAction.h"
#include "Entity\Private\ShLineBothPerpendicularVisitor.h"
#include <qpainter.h>
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity\Private\ShSnapPointFinder.h"

ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing(ShCADWidget *widget, ShActionHandler *actionHandler,
	ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, child), basePerpendicularEntity(nullptr) {

}

ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::~ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing() {

}

void ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::mouseLeftPressEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {

		if (this->search(data.point) == false) {

			this->sendFailMessage();
			this->finishDisposableSnap();
			return;
		}

		data.point = this->snap;
		dynamic_cast<ShDecoratorActionData&>(data).snapAccepted = true;

	}

	ShDisposableSnapAction::mouseLeftPressEvent(data);


	ShDrawLineAction* drawLineAction = dynamic_cast<ShDrawLineAction*>(this->actionHandler);
	drawLineAction->changeSubAction(ShDrawLineAction::SubAction::Perpendicular);

	ShSubDrawLineAction_Perpendicular *subLineAction = dynamic_cast<ShSubDrawLineAction_Perpendicular*>(drawLineAction->getSubDrawLineAction());

	subLineAction->setPerpendicularBase(this->basePerpendicularEntity);

	this->finishDisposableSnap();
}

void ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::draw(QPainter *painter) {

	if (this->valid == true) {

		if (painter->isActive() == false)
			painter->begin(this->widget);

		int dx, dy;
		this->widget->convertEntityToDevice(this->snap.x, this->snap.y, dx, dy);

		QPen oldPen = painter->pen();
		QPen pen;
		pen.setWidth(2);
		pen.setColor(QColor(000, 204, 000));
		painter->setPen(pen);

		painter->drawLine(dx - 4, dy + 4, dx + 4, dy + 4);
		painter->drawLine(dx - 4, dy + 4, dx - 4, dy - 4);
		painter->drawLine(dx - 4, dy, dx, dy);
		painter->drawLine(dx, dy + 4, dx, dy);

		painter->setPen(oldPen);
	}

	ShDecoratorAction::draw(painter);
}

void ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::invalidate(ShPoint3d &point) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(point);
}

bool ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing::search(const ShPoint3d &point) {

	this->valid = false;
	ShEntity *entity = nullptr;

	ShSearchEntityCompositeChildIncludedStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr)
		return false;

	ShSnapPointFinder finder(ObjectSnap::ObjectSnapPerpendicular, point.x, point.y, this->snap.x, this->snap.y, this->valid);
	entity->accept(&finder);

	this->basePerpendicularEntity = entity;

	return this->valid;
}


///////////////////////////////////////////////////////////////////////

ShDisposableSnapAction_DrawLineActionPerPer::ShDisposableSnapAction_DrawLineActionPerPer(ShCADWidget *widget, ShActionHandler *actionHandler,
	ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, child), basePerpendicularEntity(nullptr) {

}

ShDisposableSnapAction_DrawLineActionPerPer::~ShDisposableSnapAction_DrawLineActionPerPer() {

}

void ShDisposableSnapAction_DrawLineActionPerPer::mouseLeftPressEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {

		if (this->search(data.point) == false) {

			this->sendFailMessage();
			this->finishDisposableSnap();
			return;
		}

		dynamic_cast<ShDecoratorActionData&>(data).snapAccepted = true;
	}


	ShDrawLineAction *drawLineAction = dynamic_cast<ShDrawLineAction*>(this->actionHandler);
	ShSubDrawLineAction_Perpendicular *subDrawLineAction = dynamic_cast<ShSubDrawLineAction_Perpendicular*>(drawLineAction->getSubDrawLineAction());

	bool isValid = false;
	ShPoint3d point = this->snap;

	ShLineBothPerpendicularVisitor visitor(this->basePerpendicularEntity, point, isValid);
	subDrawLineAction->getPerpendicularBase()->accept(&visitor);

	if (isValid == true) {
		data.point = point;
		ShDisposableSnapAction::mouseLeftPressEvent(data);
	}
	else {
		//Fail.

		shCommandLogManager->appendListEditTextWith("");
		shCommandLogManager->appendList(shGetLanValue_command("Command/Line specification not valid"));
		this->actionHandler->updateCommandEditHeadTitle();
	}

	this->finishDisposableSnap();
}

void ShDisposableSnapAction_DrawLineActionPerPer::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableSnapAction_DrawLineActionPerPer::draw(QPainter *painter) {

	if (this->valid == true) {

		if (painter->isActive() == false)
			painter->begin(this->widget);

		int dx, dy;
		this->widget->convertEntityToDevice(this->snap.x, this->snap.y, dx, dy);

		QPen oldPen = painter->pen();
		QPen pen;
		pen.setWidth(2);
		pen.setColor(QColor(000, 204, 000));
		painter->setPen(pen);

		painter->drawLine(dx - 4, dy + 4, dx + 4, dy + 4);
		painter->drawLine(dx - 4, dy + 4, dx - 4, dy - 4);
		painter->drawLine(dx - 4, dy, dx, dy);
		painter->drawLine(dx, dy + 4, dx, dy);

		painter->setPen(oldPen);
	}

	ShDecoratorAction::draw(painter);
}

void ShDisposableSnapAction_DrawLineActionPerPer::invalidate(ShPoint3d &point) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(point);
}


bool ShDisposableSnapAction_DrawLineActionPerPer::search(const ShPoint3d &point) {

	this->valid = false;
	ShEntity *entity = nullptr;

	ShSearchEntityCompositeChildIncludedStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr)
		return false;

	ShSnapPointFinder finder(ObjectSnap::ObjectSnapPerpendicular, point.x, point.y, this->snap.x, this->snap.y, this->valid);
	entity->accept(&finder);

	this->basePerpendicularEntity = entity;

	return this->valid;
}