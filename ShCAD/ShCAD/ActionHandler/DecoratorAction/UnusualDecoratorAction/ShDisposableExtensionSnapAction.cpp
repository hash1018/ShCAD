
#include "ShDisposableExtensionSnapAction.h"
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity\Private\ShVertexFinder.h"
#include <qpainter.h>
#include <qtimer.h>
#include "Entity\Private\ShFootOfPerpendicularVisitor.h"
#include "Base\ShMath.h"
#include "Entity\Private\ShDrawer.h"
#include "Entity\Composite\ShEntityTable.h"
#include "Entity\Private\ShClosestIntersectionPointFinder.h"

ShExtensionStartPoint::ShExtensionStartPoint() {

}

ShExtensionStartPoint::~ShExtensionStartPoint() {

}

ShExtensionStartPoint& ShExtensionStartPoint::operator=(const ShExtensionStartPoint &other) {

	this->baseEntities = other.baseEntities;
	this->point = other.point;

	return *this;
}

void ShExtensionStartPoint::draw(QPainter *painter, ShCADWidget *widget) {

	if (painter->isActive() == false)
		painter->begin(widget);

	int dx, dy;
	widget->convertEntityToDevice(this->point.x, this->point.y, dx, dy);

	QPen oldPen = painter->pen();
	QPen pen;
	pen.setWidth(2);
	pen.setColor(QColor(000, 204, 000));
	painter->setPen(pen);

	painter->drawLine(dx - 4, dy, dx + 4, dy);
	painter->drawLine(dx, dy - 4, dx, dy + 4);

	painter->setPen(oldPen);
}

/////////////////////////////////////////////////////////////////////

ShLastDeletePoint::ShLastDeletePoint()
	:deleted(false) {

}

ShLastDeletePoint::~ShLastDeletePoint() {

}

//////////////////////////////////////////////////////////////////////

ShLastAddedPoint::ShLastAddedPoint()
	:added(false) {

}

ShLastAddedPoint::~ShLastAddedPoint() {

}


//////////////////////////////////////////////////////////////////////

ShEnabledExtensionPoints::ShEnabledExtensionPoints() {

}

ShEnabledExtensionPoints::~ShEnabledExtensionPoints() {

}

void ShEnabledExtensionPoints::clear() {

	this->baseEntities.clear();
	this->extensionFinalPoints.clear();
	this->extensionStartPoints.clear();
}

void ShEnabledExtensionPoints::draw(QPainter *painter, ShCADWidget *widget) {

	if (painter->isActive() == false)
		painter->begin(widget);

	ShApparentExtensionDrawer visitor(widget, painter);

	for (int i = 0; i < this->baseEntities.count(); i++) {

		visitor.setStart(this->extensionStartPoints.at(i));
		visitor.setEnd(this->extensionFinalPoints.at(i));
		this->baseEntities.at(i)->accept(&visitor);

	}
}

void ShEnabledExtensionPoints::updateFinalSnap(const ShPoint3d &point, ShPoint3d &snap) {

	if (this->getCount() == 0)
		return;

	if (this->getCount() == 1)
		snap = *this->extensionFinalPoints.begin();
	else if (this->getCount() >= 2) {

		bool valid;
		auto itr = this->baseEntities.begin();
		ShClosestIntersectionPointFinder visitor(point, *itr, snap, valid);
		++itr;
		(*itr)->accept(&visitor);

	}
}

//////////////////////////////////////////////////////////////////////


ShDisposableExtensionSnapAction::ShDisposableExtensionSnapAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, child) {

}

ShDisposableExtensionSnapAction::~ShDisposableExtensionSnapAction() {

}

void ShDisposableExtensionSnapAction::mouseLeftPressEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {

		this->updateExtensionStartPoints(data.point);
		
		if (this->updateEnabledExtensionPoints(data.point) == false) {
		
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

void ShDisposableExtensionSnapAction::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {


		this->updateExtensionStartPoints(data.point);
		this->updateEnabledExtensionPoints(data.point);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawActionHandler));
	}


	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableExtensionSnapAction::draw(QPainter *painter) {

	for (int i = 0; i < this->extensionStartPoints.count(); i++)
		const_cast<ShExtensionStartPoint&>(this->extensionStartPoints.at(i)).draw(painter, this->widget);

	if (this->valid == true) {

		this->enabledExtensionPoints.draw(painter, this->widget);

		if (painter->isActive() == false)
			painter->begin(widget);

		int dx, dy;
		widget->convertEntityToDevice(this->snap.x, this->snap.y, dx, dy);

		QPen oldPen = painter->pen();
		QPen pen;
		pen.setWidth(2);
		pen.setColor(QColor(255, 255, 255));
		painter->setPen(pen);

		painter->drawLine(dx - 6, dy - 6, dx + 6, dy + 6);
		painter->drawLine(dx - 6, dy + 6, dx + 6, dy - 6);

		painter->setPen(oldPen);
	}

	ShDecoratorAction::draw(painter);
}

void ShDisposableExtensionSnapAction::invalidate(ShDecoratorActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {

		this->updateExtensionStartPoints(data.point);
		this->updateEnabledExtensionPoints(data.point);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawActionHandler));
	}


	ShDisposableSnapAction::invalidate(data);
}


bool ShDisposableExtensionSnapAction::updateEnabledExtensionPoints(const ShPoint3d &point) {

	this->valid = false;
	this->enabledExtensionPoints.clear();

	if (this->extensionStartPoints.count() == 0)
		return false;

	ShPoint3d perpendicular;
	ShFootOfPerpendicularVisitor visitor(perpendicular.x, perpendicular.y, point);
	ShEntity *entity;
	double dis;

	for (int i = 0; i < this->extensionStartPoints.count(); i++) {
	
		for (int j = 0; j < this->extensionStartPoints.at(i).baseEntities.count(); j++) {

			entity = this->extensionStartPoints.at(i).baseEntities.at(j);
			entity->accept(&visitor);

			dis = math::getDistance(perpendicular.x, perpendicular.y, point.x, point.y);

			if (dis <= 15.0 / this->widget->getZoomRate() &&
				dis > 2.0 / this->widget->getZoomRate()) {

				this->enabledExtensionPoints.baseEntities.append(entity);
				this->enabledExtensionPoints.extensionStartPoints.append(this->extensionStartPoints.at(i).point);
				this->enabledExtensionPoints.extensionFinalPoints.append(perpendicular);
				this->valid = true;
				break;
				
			}
		
		}
	}

	this->enabledExtensionPoints.updateFinalSnap(point, this->snap);
	
	return this->valid;
}

void ShDisposableExtensionSnapAction::updateExtensionStartPoints(const ShPoint3d &point) {

	QLinkedList<ShEntity*> foundEntities;

	this->searchEntities(point, foundEntities);

	if (foundEntities.count() == 0)
		return;


	ShPoint3d vertexPoint;
	if (this->findClosestVertexEndAndStart(point, foundEntities, vertexPoint) == false)
		return;

	if (this->checkAlreadyExistThenRemove(point, vertexPoint) == true)
		return;

	this->addMathchedVertexEntity(point, vertexPoint);
}

void ShDisposableExtensionSnapAction::initializeLastDeletePoint() {

	this->lastDeletePoint.deleted = false;
}

void ShDisposableExtensionSnapAction::initializeLastAddedPoint() {

	this->lastAddedPoint.added = false;
}


void ShDisposableExtensionSnapAction::searchEntities(const ShPoint3d &point, QLinkedList<ShEntity*> &foundEntities) {

	//First. Search all entity that is located in point coordinate.
	ShSearchEntityDuplicateStrategy strategy(foundEntities, 100, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

}

bool ShDisposableExtensionSnapAction::findClosestVertexEndAndStart(const ShPoint3d &point, const QLinkedList<ShEntity*> &foundEntities, ShPoint3d &vertexPoint) {

	//Second. Find the closestVertex(which must be VertexEnd or VertexStart) within foundEntities.

	VertexType vertexType;
	ShNearestVertexFinder visitor(point.x, point.y, this->widget->getZoomRate(), vertexType, vertexPoint);

	auto itr = const_cast<QLinkedList<ShEntity*>&>(foundEntities).begin();
	for (itr; itr != const_cast<QLinkedList<ShEntity*>&>(foundEntities).end(); ++itr) {

		(*itr)->accept(&visitor);

		if (vertexType == VertexType::VertexEnd || vertexType == VertexType::VertexStart)
			break;
	}

	if (vertexType != VertexType::VertexEnd && vertexType != VertexType::VertexStart)
		return false;

	return true;
}

bool ShDisposableExtensionSnapAction::checkAlreadyExistThenRemove(const ShPoint3d &point, const ShPoint3d &vertexPoint) {

	for (int i = 0; i < this->extensionStartPoints.size(); i++) {

		//Already exist.
		if (const_cast<ShExtensionStartPoint&>(this->extensionStartPoints.at(i)).point == vertexPoint) {

			double zoomRate = this->widget->getZoomRate();
			double tolerance = 2.0;
			if (point.x >= vertexPoint.x - (tolerance / zoomRate) &&
				point.x <= vertexPoint.x + (tolerance / zoomRate) &&
				point.y >= vertexPoint.y - (tolerance / zoomRate) &&
				point.y <= vertexPoint.y + (tolerance / zoomRate)) {

				if (this->lastAddedPoint.added == true && this->lastAddedPoint.lastAddedPoint == vertexPoint)
					return true;

				this->lastDeletePoint.lastDeletePoint = vertexPoint;
				this->lastDeletePoint.deleted = true;
				QTimer::singleShot(1000, this, &ShDisposableExtensionSnapAction::initializeLastDeletePoint);

				this->extensionStartPoints.takeAt(i);
			}
			return true;
		}
	}

	return false;
}


void ShDisposableExtensionSnapAction::addMathchedVertexEntity(const ShPoint3d &point, const ShPoint3d &vertexPoint) {

	if (this->lastDeletePoint.deleted == true && const_cast<ShPoint3d&>(vertexPoint) == this->lastDeletePoint.lastDeletePoint)
		return;

	bool matched = false;
	VertexType matchVertexType = (VertexType)(VertexType::VertexStart | VertexType::VertexEnd);
	PointAndVertexTypeMathchedEntityFinder visitor(vertexPoint, matchVertexType, matched);
	ShExtensionStartPoint data;
	data.point = vertexPoint;
	

	auto itr = this->widget->getEntityTable().turnOnLayerBegin();
	for (itr; itr != this->widget->getEntityTable().turnOnLayerEnd(); ++itr) {

		(*itr)->accept(&visitor);

		if (matched == true) {

			for (int i = 0; i < this->extensionStartPoints.count(); i++) {
				if (this->extensionStartPoints.at(i).baseEntities.contains((*itr)) == true)
					return;
			}

			data.baseEntities.append((*itr));
		}
	}

	this->extensionStartPoints.append(data);

	this->lastAddedPoint.added = true;
	this->lastAddedPoint.lastAddedPoint = vertexPoint;
	QTimer::singleShot(1000, this, &ShDisposableExtensionSnapAction::initializeLastAddedPoint);
}