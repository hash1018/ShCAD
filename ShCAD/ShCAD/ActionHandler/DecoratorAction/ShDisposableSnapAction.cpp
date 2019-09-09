
#include "ShDisposableSnapAction.h"
#include "ActionHandler\Private\ShDecorateActionStrategy.h"
#include <QKeyEvent>
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity\Private\ShSnapPointFinder.h"
#include <qpainter.h>
#include "Entity\Private\ShFootOfPerpendicularVisitor.h"
#include "Entity\Private\ShClosestIntersectionPointFinder.h"


ShDisposableSnapAction::ShDisposableSnapAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShDecoratorAction(widget, actionHandler, child), valid(false) {

}

ShDisposableSnapAction::~ShDisposableSnapAction() {

}


void ShDisposableSnapAction::keyPressEvent(ShActionData &data) {
	

	ShDecoratorAction::keyPressEvent(data);

	if (data.keyEvent->key() == Qt::Key::Key_Return ||
		data.keyEvent->key() == Qt::Key_Enter) {
		this->widget->update(DrawType::DrawCaptureImage); //Erase drawn snap.
		this->sendFailMessage();
		this->finishDisposableSnap();
		return;
	}

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
		dynamic_cast<ShDecoratorActionData&>(data).orthAccepted = false;

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

void ShDisposableSnapAction_End::invalidate(ShDecoratorActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(data);
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
		dynamic_cast<ShDecoratorActionData&>(data).orthAccepted = false;

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

void ShDisposableSnapAction_Mid::invalidate(ShDecoratorActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(data);
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
		dynamic_cast<ShDecoratorActionData&>(data).orthAccepted = false;

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

void ShDisposableSnapAction_Center::invalidate(ShDecoratorActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(data);
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
		dynamic_cast<ShDecoratorActionData&>(data).orthAccepted = false;

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

void ShDisposableSnapAction_Quadrant::invalidate(ShDecoratorActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(data);
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
	:ShDisposableSnapAction(widget, actionHandler, child), firstBaseEntity(nullptr), foundOnlyOne(false), status(PickedNothing) {

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
		//Success
		else {
		
			if (this->status == PickedNothing) {

				if (this->foundOnlyOne == true) {

					this->status = PickedBaseEntity;
					shCommandLogManager->appendHeadTitle("and ");
					return;
				}
			}
		}

		data.point = this->snap;
		dynamic_cast<ShDecoratorActionData&>(data).orthAccepted = false;

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

		painter->drawLine(dx - 4, dy - 4, dx + 4, dy + 4);
		painter->drawLine(dx + 4, dy - 4, dx - 4, dy + 4);

		if (this->foundOnlyOne == true && this->status == PickedNothing) {

			painter->drawLine(dx + 4, dy + 4, dx + 6, dy + 4);
			painter->drawLine(dx + 10, dy + 4, dx + 14, dy + 4);
			painter->drawLine(dx + 18, dy + 4, dx + 22, dy + 4);
		}

		painter->setPen(oldPen);
	}

	ShDecoratorAction::draw(painter);
}

void ShDisposableSnapAction__Intersection::invalidate(ShDecoratorActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {
		if (this->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(data);
}

bool ShDisposableSnapAction__Intersection::search(const ShPoint3d &point) {

	this->valid = false;
	this->foundOnlyOne = false;

	QLinkedList<ShEntity*> foundEntities;
	ShSearchEntityDuplicateStrategy strategy(foundEntities, 2, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (foundEntities.count() == 0)
		return false;

	if (this->status == PickedNothing) {

		if (foundEntities.count() == 1) {

			ShFootOfPerpendicularVisitor visitor(this->snap.x, this->snap.y, point);
			(*foundEntities.begin())->accept(&visitor);
			this->valid = true;
			this->foundOnlyOne = true;
			this->firstBaseEntity = (*foundEntities.begin());
		}
		else if (foundEntities.count() >= 2) {

			auto itr = foundEntities.begin();
			ShClosestIntersectionPointFinder visitor(point, *itr, this->snap, this->valid);
			++itr;
			(*itr)->accept(&visitor);
		}
	}
	else if (this->status == PickedBaseEntity) {
	
		if (foundEntities.count() == 1) {
		
			ShClosestIntersectionPointFinder visitor(point, this->firstBaseEntity, this->snap, this->valid);
			(*foundEntities.begin())->accept(&visitor);

		}
		else if (foundEntities.count() >= 2) {
		
			auto itr = foundEntities.begin();
			ShClosestIntersectionPointFinder visitor(point, *itr, this->snap, this->valid);
			++itr;
			(*itr)->accept(&visitor);
		}
	}
	
	return this->valid;
}

void ShDisposableSnapAction__Intersection::sendFailMessage() {

	shCommandLogManager->appendListEditTextWith("");
	shCommandLogManager->appendList(shGetLanValue_command("Command/No Intersection found for specified point"));
	shCommandLogManager->appendList(shGetLanValue_command("Command/No snap point found"));
	this->actionHandler->updateCommandEditHeadTitle();
}


////////////////////////////////////////////////////////////////////////

ShDisposableSnapAction_ApparentIntersection::ShDisposableSnapAction_ApparentIntersection(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShDisposableSnapAction__Intersection(widget, actionHandler, child) {

}

ShDisposableSnapAction_ApparentIntersection::~ShDisposableSnapAction_ApparentIntersection() {

}

void ShDisposableSnapAction_ApparentIntersection::draw(QPainter *painter) {

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

		painter->drawLine(dx - 4, dy - 4, dx + 4, dy + 4);
		painter->drawLine(dx + 4, dy - 4, dx - 4, dy + 4);

		if (this->foundOnlyOne == true && this->status == PickedNothing) {

			painter->drawRect(dx - 4, dy - 4, 8, 8);

			painter->drawLine(dx + 4, dy + 4, dx + 6, dy + 4);
			painter->drawLine(dx + 10, dy + 4, dx + 14, dy + 4);
			painter->drawLine(dx + 18, dy + 4, dx + 22, dy + 4);
		}

		painter->setPen(oldPen);
	}

	ShDecoratorAction::draw(painter);
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
		dynamic_cast<ShDecoratorActionData&>(data).orthAccepted = false;

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

void ShDisposableSnapAction_Perpendicular::invalidate(ShDecoratorActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {

		if (this->search(data.point, draft.getSnapBasePoint().x, draft.getSnapBasePoint().y) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}

	ShDisposableSnapAction::invalidate(data);
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

