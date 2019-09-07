
#include "ShDisposableSnapAction.h"
#include "ActionHandler\Private\ShDecorateActionStrategy.h"
#include "ActionHandler\DrawAction\ShDrawLineAction.h"
#include "Entity\Private\ShLineBothPerpendicularVisitor.h"
#include <QKeyEvent>
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity\Private\ShSnapPointFinder.h"
#include <qpainter.h>


ShDisposableSnapAction::ShDisposableSnapAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShDecoratorAction(widget, actionHandler, child), valid(false) {

}

ShDisposableSnapAction::~ShDisposableSnapAction() {

}


void ShDisposableSnapAction::keyPressEvent(ShActionData &data) {
	
	ShDecoratorAction::keyPressEvent(data);

	if (data.keyEvent->key() == Qt::Key::Key_Escape) {
		this->finishDisposableSnap();
	}
}


void ShDisposableSnapAction::finishDisposableSnap() {

	ShDecorateDisposableSnapActionStrategy strategy(ObjectSnap::ObjectSnapNothing);
	this->widget->changeAction(strategy);
}

void ShDisposableSnapAction::sendFailMessage() {

	shCommandLogManager->appendListEditTextWith("");
	shCommandLogManager->appendList(shGetLanValue_command("Command/No snap point found"));
	this->actionHandler->updateCommandEditHeadTitle();
}

/////////////////////////////////////////////////////////////////
/*

ShDisposableSnapAction_General::ShDisposableSnapAction_General(ShCADWidget *widget, ShActionHandler *actionHandler, ObjectSnap objectSnap, ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, objectSnap, child) {

}


ShDisposableSnapAction_General::~ShDisposableSnapAction_General() {


}

void ShDisposableSnapAction_General::mouseLeftPressEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
	
		if (this->strategy->search(data.point) == false) {
		
			this->sendFailMessage();
			this->finishDisposableSnap();
			return;
		}

		data.point = this->strategy->getSnap();
		dynamic_cast<ShDecoratorActionData&>(data).snapAccepted = true;

	}

	ShDisposableSnapAction::mouseLeftPressEvent(data);

	this->finishDisposableSnap();
}

void ShDisposableSnapAction_General::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->strategy->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableSnapAction_General::invalidate(ShPoint3d &point) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->strategy->search(point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(point);
}


*/

////////////////////////////////////////////////////////////////////////

ShDisposableSnapAction_End::ShDisposableSnapAction_End(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, child) {

}

ShDisposableSnapAction_End::~ShDisposableSnapAction_End() {

}

void ShDisposableSnapAction_End::mouseLeftPressEvent(ShActionData &data) {

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

	this->finishDisposableSnap();
}

void ShDisposableSnapAction_End::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableSnapAction_End::draw(QPainter *painter) {

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

		painter->drawRect(dx - 4, dy - 4, 8, 8);

		painter->setPen(oldPen);
	}

	ShDecoratorAction::draw(painter);
}

void ShDisposableSnapAction_End::invalidate(ShPoint3d &point) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(point);
}

bool ShDisposableSnapAction_End::search(const ShPoint3d &point) {

	this->valid = false;
	ShEntity *entity = nullptr;

	ShSearchEntityCompositeChildIncludedStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr)
		return false;

	ShSnapPointFinder finder(ObjectSnap::ObjectSnapEndPoint, point.x, point.y, this->snap.x, this->snap.y, this->valid);
	entity->accept(&finder);

	return this->valid;
}

////////////////////////////////////////////////////////////////////////


ShDisposableSnapAction_Mid::ShDisposableSnapAction_Mid(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, child) {

}

ShDisposableSnapAction_Mid::~ShDisposableSnapAction_Mid() {

}

void ShDisposableSnapAction_Mid::mouseLeftPressEvent(ShActionData &data) {

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

	this->finishDisposableSnap();
}

void ShDisposableSnapAction_Mid::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableSnapAction_Mid::draw(QPainter *painter) {

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
		painter->drawLine(dx - 4, dy + 4, dx, dy - 4);
		painter->drawLine(dx + 4, dy + 4, dx, dy - 4);

		painter->setPen(oldPen);
	}

	ShDecoratorAction::draw(painter);
}

void ShDisposableSnapAction_Mid::invalidate(ShPoint3d &point) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(point);
}

bool ShDisposableSnapAction_Mid::search(const ShPoint3d &point) {

	this->valid = false;
	ShEntity *entity = nullptr;

	ShSearchEntityCompositeChildIncludedStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr)
		return false;

	ShSnapPointFinder finder(ObjectSnap::ObjectSnapMidPoint, point.x, point.y, this->snap.x, this->snap.y, this->valid);
	entity->accept(&finder);

	return this->valid;
}

/////////////////////////////////////////////////////////////////////////

ShDisposableSnapAction_Center::ShDisposableSnapAction_Center(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, child) {

}

ShDisposableSnapAction_Center::~ShDisposableSnapAction_Center() {

}

void ShDisposableSnapAction_Center::mouseLeftPressEvent(ShActionData &data) {

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

	this->finishDisposableSnap();
}

void ShDisposableSnapAction_Center::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableSnapAction_Center::draw(QPainter *painter) {

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

		painter->drawEllipse(dx - 4, dy - 4, 8, 8);

		painter->setPen(oldPen);
	}

	ShDecoratorAction::draw(painter);
}

void ShDisposableSnapAction_Center::invalidate(ShPoint3d &point) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(point);
}

bool ShDisposableSnapAction_Center::search(const ShPoint3d &point) {

	this->valid = false;
	ShEntity *entity = nullptr;

	ShSearchEntityCompositeChildIncludedStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr)
		return false;

	ShSnapPointFinder finder(ObjectSnap::ObjectSnapCenter, point.x, point.y, this->snap.x, this->snap.y, this->valid);
	entity->accept(&finder);

	return this->valid;
}

/////////////////////////////////////////////////////////////////////////


ShDisposableSnapAction_Quadrant::ShDisposableSnapAction_Quadrant(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, child) {

}

ShDisposableSnapAction_Quadrant::~ShDisposableSnapAction_Quadrant() {

}

void ShDisposableSnapAction_Quadrant::mouseLeftPressEvent(ShActionData &data) {

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

	this->finishDisposableSnap();
}

void ShDisposableSnapAction_Quadrant::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableSnapAction_Quadrant::draw(QPainter *painter) {

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

		painter->drawLine(dx, dy - 4, dx - 4, dy);
		painter->drawLine(dx - 4, dy, dx, dy + 4);
		painter->drawLine(dx, dy + 4, dx + 4, dy);
		painter->drawLine(dx + 4, dy, dx, dy - 4);

		painter->setPen(oldPen);
	}

	ShDecoratorAction::draw(painter);
}

void ShDisposableSnapAction_Quadrant::invalidate(ShPoint3d &point) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(point);
}

bool ShDisposableSnapAction_Quadrant::search(const ShPoint3d &point) {

	this->valid = false;
	ShEntity *entity = nullptr;

	ShSearchEntityCompositeChildIncludedStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr)
		return false;

	ShSnapPointFinder finder(ObjectSnap::ObjectSnapQuadrant, point.x, point.y, this->snap.x, this->snap.y, this->valid);
	entity->accept(&finder);

	return this->valid;
}


/////////////////////////////////////////////////////////////////////////

ShDisposableSnapAction__Intersection::ShDisposableSnapAction__Intersection(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, child) {

}

ShDisposableSnapAction__Intersection::~ShDisposableSnapAction__Intersection() {

}

void ShDisposableSnapAction__Intersection::mouseLeftPressEvent(ShActionData &data) {

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

	this->finishDisposableSnap();
}

void ShDisposableSnapAction__Intersection::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableSnapAction__Intersection::draw(QPainter *painter) {

}

void ShDisposableSnapAction__Intersection::invalidate(ShPoint3d &point) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(point);
}

bool ShDisposableSnapAction__Intersection::search(const ShPoint3d &point) {

	return this->valid;
}


////////////////////////////////////////////////////////////////////////


ShDisposableSnapAction_Perpendicular::ShDisposableSnapAction_Perpendicular(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, child) {

}

ShDisposableSnapAction_Perpendicular::~ShDisposableSnapAction_Perpendicular() {

}


void ShDisposableSnapAction_Perpendicular::mouseLeftPressEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {

		if (this->search(data.point, draft.getSnapBasePoint().x, draft.getSnapBasePoint().y) == false) {

			this->sendFailMessage();
			this->finishDisposableSnap();
			return;
		}

		data.point = this->snap;
		dynamic_cast<ShDecoratorActionData&>(data).snapAccepted = true;

	}

	ShDisposableSnapAction::mouseLeftPressEvent(data);

	this->finishDisposableSnap();
}

void ShDisposableSnapAction_Perpendicular::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {

		if (this->search(data.point, draft.getSnapBasePoint().x, draft.getSnapBasePoint().y) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableSnapAction_Perpendicular::draw(QPainter *painter) {

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

void ShDisposableSnapAction_Perpendicular::invalidate(ShPoint3d &point) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {

		if (this->search(point, draft.getSnapBasePoint().x, draft.getSnapBasePoint().y) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(point);
}

bool ShDisposableSnapAction_Perpendicular::search(const ShPoint3d &point) {

	return false;
}

bool ShDisposableSnapAction_Perpendicular::search(const ShPoint3d &point, double perpendicularX, double perpendicularY) {

	this->valid = false;
	ShEntity *entity = nullptr;

	ShSearchEntityCompositeChildIncludedStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr)
		return false;

	ShSnapPointFinder finder(ObjectSnap::ObjectSnapPerpendicular, point.x, point.y, this->snap.x, this->snap.y, this->valid,
		perpendicularX, perpendicularY);

	entity->accept(&finder);

	return this->valid;
}

///////////////////////////////////////////////////////////////////


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
	:ShDisposableSnapAction(widget, actionHandler, child),basePerpendicularEntity(nullptr) {

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