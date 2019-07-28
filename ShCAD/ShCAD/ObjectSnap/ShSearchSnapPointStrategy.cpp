
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