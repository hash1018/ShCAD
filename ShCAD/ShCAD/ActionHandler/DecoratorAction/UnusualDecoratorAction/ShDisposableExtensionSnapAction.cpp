
#include "ShDisposableExtensionSnapAction.h"
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity\Private\ShVertexFinder.h"
#include <qpainter.h>
#include <qtimer.h>


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
	
	}


	ShDecoratorAction::draw(painter);
}

void ShDisposableExtensionSnapAction::invalidate(ShDecoratorActionData &data) {

}


void ShDisposableExtensionSnapAction::updateExtensionBaseData(const ShPoint3d &point) {

	QLinkedList<ShEntity*> foundEntities;

	//First. Search all entity that is located in point coordinate.
	ShSearchEntityDuplicateStrategy strategy(foundEntities, 100, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (foundEntities.count() == 0)
		return;


	//Second. Find the closestVertex(which must be VertexEnd or VertexStart) within foundEntities.
	VertexType vertexType;
	ShPoint3d vertexPoint;
	ShNearestVertexFinder visitor(point.x, point.y, this->widget->getZoomRate(), vertexType, vertexPoint);

	auto itr = foundEntities.begin();
	for (itr; itr != foundEntities.end(); ++itr) {

		(*itr)->accept(&visitor);

		if (vertexType == VertexType::VertexEnd || vertexType == VertexType::VertexStart)
			break;
	}

	if (vertexType != VertexType::VertexEnd && vertexType != VertexType::VertexStart)
		return;


	//Third. With Searched VertexType and VertexPoint, find all entity that has same vertex Coordinate to vertexPoint above found.
	if (vertexType == VertexType::VertexEnd || vertexType == VertexType::VertexStart) {

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
						return;

					this->lastDeletePoint.lastDeletePoint = vertexPoint;
					this->lastDeletePoint.deleted = true;
					QTimer::singleShot(1000, this, &ShDisposableExtensionSnapAction::initializeLastDeletePoint);

					this->extensionBaseDatas.takeAt(i);
				}
				return;
			}
		}

		//Doesn't exist in the list. Howerver, if vertexPoint was deleted within 1sec, cancel below task.

		if (this->lastDeletePoint.deleted == true && vertexPoint == this->lastDeletePoint.lastDeletePoint)
			return;

		bool mathched = false;
		VertexType matchVertexType = (VertexType)(VertexType::VertexStart | VertexType::VertexEnd);
		PointAndVertexTypeMathchedEntityFinder visitor(vertexPoint, vertexType, mathched);
		ShExtensionBaseData data;
		data.point = vertexPoint;
		
		itr = foundEntities.begin();
		for (itr; itr != foundEntities.end(); ++itr) {
		
			(*itr)->accept(&visitor);
			if (mathched == true)
				data.baseEntities.append((*itr));
		}

		this->extensionBaseDatas.append(data);

		this->lastAddedPoint.added = true;
		this->lastAddedPoint.lastAddedPoint = vertexPoint;
		QTimer::singleShot(1000, this, &ShDisposableExtensionSnapAction::initializeLastAddedPoint);
		
	}
}

void ShDisposableExtensionSnapAction::initializeLastDeletePoint() {

	this->lastDeletePoint.deleted = false;
}

void ShDisposableExtensionSnapAction::initializeLastAddedPoint() {

	this->lastAddedPoint.added = false;
}