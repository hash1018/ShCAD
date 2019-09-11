
#include "ShDisposableExtensionSnapAction.h"
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity\Private\ShVertexFinder.h"
#include <qpainter.h>
#include <qtimer.h>
#include "Entity\Private\ShFootOfPerpendicularVisitor.h"
#include "Base\ShMath.h"
#include "Entity\Private\ShDrawer.h"

ShExtensionBaseData::ShExtensionBaseData() {

}

ShExtensionBaseData::~ShExtensionBaseData() {

}

ShExtensionBaseData& ShExtensionBaseData::operator=(const ShExtensionBaseData &other) {

	this->baseEntities = other.baseEntities;
	this->point = other.point;

	return *this;
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

ShExtensionBaseLine::ShExtensionBaseLine() {

}

ShExtensionBaseLine::~ShExtensionBaseLine() {

}

void ShExtensionBaseLine::clear() {

	this->baseLineEntities.clear();
	this->extensionFinalPoints.clear();
	this->extensionStartPoints.clear();
}

//////////////////////////////////////////////////////////////////////


ShDisposableExtensionSnapAction::ShDisposableExtensionSnapAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child)
	:ShDisposableSnapAction(widget, actionHandler, child) {

}

ShDisposableExtensionSnapAction::~ShDisposableExtensionSnapAction() {

}

void ShDisposableExtensionSnapAction::mouseLeftPressEvent(ShActionData &data) {

}

void ShDisposableExtensionSnapAction::mouseMoveEvent(ShActionData &data) {

	ShAvailableDraft draft = this->actionHandler->getAvailableDraft();

	if (draft.getAvailableSnap() == true) {


		this->updateExtensionBaseData(data.point);
		this->searchExtensionLine(data.point);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawActionHandler));
	}


	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableExtensionSnapAction::draw(QPainter *painter) {

	if (this->extensionBaseDatas.count() > 0) {

		if (painter->isActive() == false)
			painter->begin(this->widget);

		ShPoint3d point;
		for (int i = 0; i < this->extensionBaseDatas.count(); i++) {
		
			point = this->extensionBaseDatas.at(i).point;

			int dx, dy;
			this->widget->convertEntityToDevice(point.x, point.y, dx, dy);

			QPen oldPen = painter->pen();
			QPen pen;
			pen.setWidth(2);
			pen.setColor(QColor(000, 204, 000));
			painter->setPen(pen);

			painter->drawLine(dx - 4, dy, dx + 4, dy);
			painter->drawLine(dx, dy - 4, dx, dy + 4);

			painter->setPen(oldPen);
		}

		ShApparentExtensionDrawer visitor(this->widget, painter);

		for (int i = 0; i < this->extensionBaseLine.baseLineEntities.count(); i++) {
		
			visitor.setStart(this->extensionBaseLine.extensionStartPoints.at(i));
			visitor.setEnd(this->extensionBaseLine.extensionFinalPoints.at(i));
			this->extensionBaseLine.baseLineEntities.at(i)->accept(&visitor);

		}
	
	}


	ShDecoratorAction::draw(painter);
}

void ShDisposableExtensionSnapAction::invalidate(ShDecoratorActionData &data) {

}


bool ShDisposableExtensionSnapAction::searchExtensionLine(const ShPoint3d &point) {

	this->extensionBaseLine.clear();

	if (this->extensionBaseDatas.count() == 0)
		return false;

	ShPoint3d perpendicular;
	ShFootOfPerpendicularVisitor visitor(perpendicular.x, perpendicular.y, point);
	ShEntity *entity;
	double dis;

	for (int i = 0; i < this->extensionBaseDatas.count(); i++) {
	
		for (int j = 0; j < this->extensionBaseDatas.at(i).baseEntities.count(); j++) {

			entity = this->extensionBaseDatas.at(i).baseEntities.at(j);
			entity->accept(&visitor);

			dis = math::getDistance(perpendicular.x, perpendicular.y, point.x, point.y);

			if (dis <= 10.0 / this->widget->getZoomRate() &&
				dis > 2.0 / this->widget->getZoomRate()) {

				this->extensionBaseLine.baseLineEntities.append(entity);
				this->extensionBaseLine.extensionStartPoints.append(this->extensionBaseDatas.at(i).point);
				this->extensionBaseLine.extensionFinalPoints.append(perpendicular);
				break;
				
			}
		
		}
	}

	if (this->extensionBaseLine.getCount() != 0)
		return true;

	return false;
}

void ShDisposableExtensionSnapAction::updateExtensionBaseData(const ShPoint3d &point) {

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

	for (int i = 0; i < this->extensionBaseDatas.size(); i++) {

		//Already exist.
		if (const_cast<ShExtensionBaseData&>(this->extensionBaseDatas.at(i)).point == vertexPoint) {

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

				this->extensionBaseDatas.takeAt(i);
			}
			return true;
		}
	}

	return false;
}

#include <qdebug.h>
void ShDisposableExtensionSnapAction::addMathchedVertexEntity(const ShPoint3d &point, const ShPoint3d &vertexPoint) {

	if (this->lastDeletePoint.deleted == true && const_cast<ShPoint3d&>(vertexPoint) == this->lastDeletePoint.lastDeletePoint)
		return;

	bool matched = false;
	VertexType matchVertexType = (VertexType)(VertexType::VertexStart | VertexType::VertexEnd);
	PointAndVertexTypeMathchedEntityFinder visitor(vertexPoint, matchVertexType, matched);
	ShExtensionBaseData data;
	data.point = vertexPoint;
	

	auto itr = this->widget->getEntityTable().turnOnLayerBegin();
	for (itr; itr != this->widget->getEntityTable().turnOnLayerEnd(); ++itr) {

		(*itr)->accept(&visitor);

		if (matched == true)
			data.baseEntities.append((*itr));
	}

	
	this->extensionBaseDatas.append(data);

	this->lastAddedPoint.added = true;
	this->lastAddedPoint.lastAddedPoint = vertexPoint;
	QTimer::singleShot(1000, this, &ShDisposableExtensionSnapAction::initializeLastAddedPoint);
}