
#include "ShSearchSnapPointStrategy.h"
#include "Interface\ShCADWidget.h"
#include <qpainter.h>
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity\Private\ShSnapPointFinder.h"

ShSearchSnapPointStrategy::ShSearchSnapPointStrategy(ShCADWidget *widget)
	:widget(widget), isValid(false) {

}

ShSearchSnapPointStrategy::~ShSearchSnapPointStrategy() {

}

////////////////////////////////////////////////////////

ShSearchSnapPointStrategy_Nothing::ShSearchSnapPointStrategy_Nothing(ShCADWidget *widget)
	:ShSearchSnapPointStrategy(widget) {


}

ShSearchSnapPointStrategy_Nothing::~ShSearchSnapPointStrategy_Nothing() {


}

bool ShSearchSnapPointStrategy_Nothing::search(const ShPoint3d &point) {

	return false;
}

ObjectSnap ShSearchSnapPointStrategy_Nothing::getType() {

	return ObjectSnap::ObjectSnapNothing;
}

void ShSearchSnapPointStrategy_Nothing::draw(QPainter *painter) {

}

/////////////////////////////////////////////////////

ShSearchSnapPointStrategy_End::ShSearchSnapPointStrategy_End(ShCADWidget *widget)
	:ShSearchSnapPointStrategy(widget) {


}

ShSearchSnapPointStrategy_End::~ShSearchSnapPointStrategy_End() {

}

bool ShSearchSnapPointStrategy_End::search(const ShPoint3d &point) {

	ShEntity *entity = nullptr;

	ShSearchEntityCompositeChildIncludedStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr)
		return false;

	this->isValid = false;

	ShSnapPointFinder finder(ObjectSnap::ObjectSnapEndPoint, point.x, point.y, this->snap.x, this->snap.y, this->isValid);
	entity->accept(&finder);

	return this->isValid;
}

ObjectSnap ShSearchSnapPointStrategy_End::getType() {

	return ObjectSnap::ObjectSnapEndPoint;
}

void ShSearchSnapPointStrategy_End::draw(QPainter *painter) {

	if (this->isValid == false)
		return;

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

////////////////////////////////////////////////////////////////////////


ShSearchSnapPointStrategy_Mid::ShSearchSnapPointStrategy_Mid(ShCADWidget *widget)
	:ShSearchSnapPointStrategy(widget) {

}

ShSearchSnapPointStrategy_Mid::~ShSearchSnapPointStrategy_Mid() {

}

bool ShSearchSnapPointStrategy_Mid::search(const ShPoint3d &point) {

	ShEntity *entity = nullptr;

	ShSearchEntityCompositeChildIncludedStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr)
		return false;

	this->isValid = false;

	ShSnapPointFinder finder(ObjectSnap::ObjectSnapMidPoint, point.x, point.y, this->snap.x, this->snap.y, this->isValid);
	entity->accept(&finder);

	return this->isValid;
}

ObjectSnap ShSearchSnapPointStrategy_Mid::getType() {

	return ObjectSnap::ObjectSnapMidPoint;
}

void ShSearchSnapPointStrategy_Mid::draw(QPainter *painter) {

	if (this->isValid == false)
		return;

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



/////////////////////////////////////////////////////////


ShSearchSnapPointStrategy_Center::ShSearchSnapPointStrategy_Center(ShCADWidget *widget)
	:ShSearchSnapPointStrategy(widget) {

}

ShSearchSnapPointStrategy_Center::~ShSearchSnapPointStrategy_Center() {

}

bool ShSearchSnapPointStrategy_Center::search(const ShPoint3d &point) {

	ShEntity *entity = nullptr;

	ShSearchEntityCompositeChildIncludedStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr)
		return false;

	this->isValid = false;

	ShSnapPointFinder finder(ObjectSnap::ObjectSnapCenter, point.x, point.y, this->snap.x, this->snap.y, this->isValid);
	entity->accept(&finder);

	return this->isValid;
}

ObjectSnap ShSearchSnapPointStrategy_Center::getType() {

	return ObjectSnap::ObjectSnapCenter;
}

void ShSearchSnapPointStrategy_Center::draw(QPainter *painter) {

	if (this->isValid == false)
		return;

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



//////////////////////////////////////////////////////////


ShSearchSnapPointStrategy_Quadrant::ShSearchSnapPointStrategy_Quadrant(ShCADWidget *widget)
	:ShSearchSnapPointStrategy(widget) {

}

ShSearchSnapPointStrategy_Quadrant::~ShSearchSnapPointStrategy_Quadrant() {

}

bool ShSearchSnapPointStrategy_Quadrant::search(const ShPoint3d &point) {

	ShEntity *entity = nullptr;

	ShSearchEntityCompositeChildIncludedStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr)
		return false;

	this->isValid = false;

	ShSnapPointFinder finder(ObjectSnap::ObjectSnapQuadrant, point.x, point.y, this->snap.x, this->snap.y, this->isValid);
	entity->accept(&finder);

	return this->isValid;
}

ObjectSnap ShSearchSnapPointStrategy_Quadrant::getType() {

	return ObjectSnap::ObjectSnapQuadrant;
}

void ShSearchSnapPointStrategy_Quadrant::draw(QPainter *painter) {

	if (this->isValid == false)
		return;

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



//////////////////////////////////////////////////////////


ShSearchSnapPointStrategy_Perpendicular::ShSearchSnapPointStrategy_Perpendicular(ShCADWidget *widget)
	:ShSearchSnapPointStrategy(widget) {

}

ShSearchSnapPointStrategy_Perpendicular::~ShSearchSnapPointStrategy_Perpendicular() {

}

bool ShSearchSnapPointStrategy_Perpendicular::search(const ShPoint3d &point) {

	ShEntity *entity = nullptr;

	ShSearchEntityCompositeChildIncludedStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr)
		return false;

	this->isValid = false;

	ShSnapPointFinder finder(ObjectSnap::ObjectSnapPerpendicular, point.x, point.y, this->snap.x, this->snap.y, this->isValid);
	entity->accept(&finder);

	this->perpendicularBaseEntity = entity;

	return this->isValid;
}

bool ShSearchSnapPointStrategy_Perpendicular::search(const ShPoint3d &point, double perpendicularX, double perpendicularY) {

	ShEntity *entity = nullptr;

	ShSearchEntityCompositeChildIncludedStrategy strategy(&entity, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (entity == nullptr)
		return false;

	this->isValid = false;

	ShSnapPointFinder finder(ObjectSnap::ObjectSnapPerpendicular, point.x, point.y, this->snap.x, this->snap.y, this->isValid,
		perpendicularX, perpendicularY);

	entity->accept(&finder);

	this->perpendicularBaseEntity = entity;

	return this->isValid;
}

ObjectSnap ShSearchSnapPointStrategy_Perpendicular::getType() {

	return ObjectSnap::ObjectSnapPerpendicular;
}

void ShSearchSnapPointStrategy_Perpendicular::draw(QPainter *painter) {

	if (this->isValid == false)
		return;

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

