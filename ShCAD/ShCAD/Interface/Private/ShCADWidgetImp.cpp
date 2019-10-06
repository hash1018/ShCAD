
#include "ShCADWidgetImp.h"
#include "Interface\ShCADWidget.h"
#include "ActionHandler\ShActionHandlerProxy.h"
#include "UnRedo\ShTransactionStack.h"
#include "Base\ShLayerTable.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include <qpainter.h>
#include "ShCADWidgetDrawStrategy.h"
#include <QMouseEvent>
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "Event\ShNotifyEvent.h"
#include "Base\ShMath.h"
#include "Entity\Private\ShPloter.h"

ShCADWidgetImp::ShCADWidgetImp(ShCADWidget *widget)
	:widget(widget), zoomRate(1.0), actionHandlerProxy(nullptr), undoStack(nullptr),
	redoStack(nullptr), layerTable(nullptr), entityTable(nullptr), selectedEntities(nullptr) {


}

ShCADWidgetImp::~ShCADWidgetImp() {

	if (this->actionHandlerProxy != nullptr)
		delete this->actionHandlerProxy;

	if (this->undoStack != nullptr)
		delete this->undoStack;

	if (this->redoStack != nullptr)
		delete this->redoStack;

	if (this->layerTable != nullptr)
		delete this->layerTable;

	if (this->entityTable != nullptr)
		delete this->entityTable;

	if (this->selectedEntities != nullptr)
		delete this->selectedEntities;

	this->rubberBand.clear();
}

void ShCADWidgetImp::init() {

	this->actionHandlerProxy = new ShActionHandlerProxy(this->widget);
	this->axis.setCenter(ShPoint3d(100, 500));

	this->undoStack = new ShTransactionStack;
	this->redoStack = new ShTransactionStack;

	this->layerTable = new ShLayerTable;

	this->entityTable = new ShEntityTable(this->layerTable);

	this->selectedEntities = new ShSelectedEntities;
}

void ShCADWidgetImp::changeAction(ShChangeActionStrategy &strategy) {

	strategy.widget = this->widget;
	strategy.change();
}

void ShCADWidgetImp::convertDeviceToEntity(const int &x, const int &y, double &ex, double &ey) {

	ex = (x + this->scroll.horizontal - (this->axis.getCenter().x*this->zoomRate))*1.000 / this->zoomRate;
	ey = (-1 * (y + this->scroll.vertical - (this->axis.getCenter().y)*this->zoomRate))*1.000 / this->zoomRate;
}

void ShCADWidgetImp::convertEntityToDevice(const double &x, const double &y, int &dx, int &dy) {

	double tempX = ((x*this->zoomRate) - this->scroll.horizontal + (this->axis.getCenter().x*this->zoomRate));
	double tempY = (-1 * ((y*this->zoomRate) + this->scroll.vertical - (this->axis.getCenter().y*this->zoomRate)));

	dx = math::toInt(tempX);
	dy = math::toInt(tempY);
}


void ShCADWidgetImp::paintGL() {

	QPainter painter(this->widget);

	ShCADWidgetDrawStrategy strategy(this->widget, &painter, this->widget->getDrawBuffer().drawType);
	strategy.draw();
}

void ShCADWidgetImp::mousePressEvent(QMouseEvent *event) {

	if (event->buttons() & Qt::MiddleButton) {
		ShChangeTemporaryPanStrategy strategy(this->actionHandlerProxy->getCurrentAction());
		this->changeAction(strategy);
	}


	if (event->buttons() & Qt::LeftButton)
		this->actionHandlerProxy->mouseLeftPressEvent(event);
	else if (event->buttons() & Qt::MiddleButton)
		this->actionHandlerProxy->mouseMidPressEvent(event);
	else if (event->buttons() & Qt::RightButton)
		this->actionHandlerProxy->mouseRightPressEvent(event);
}

void ShCADWidgetImp::mouseMoveEvent(QMouseEvent *event) {

	this->convertDeviceToEntity(event->x(), event->y(), this->coordinate.x, this->coordinate.y);

	ShMousePositionChangedEvent notifyEvent(this->coordinate);
	this->widget->notify(&notifyEvent);

	this->actionHandlerProxy->mouseMoveEvent(event);
}

void ShCADWidgetImp::mouseReleaseEvent(QMouseEvent *event) {

	this->actionHandlerProxy->mouseReleaseEvent(event);
}

void ShCADWidgetImp::keyPressEvent(QKeyEvent *event) {

	this->actionHandlerProxy->keyPressEvent(event);
}

void ShCADWidgetImp::wheelEvent(QWheelEvent *event) {

	this->convertDeviceToEntity(event->x(), event->y(), this->coordinate.x, this->coordinate.y);

	if (event->delta() > 0) {

		if (this->zoomRate < 15 && this->zoomRate >= 1)
			this->zoomRate++;
		else if (this->zoomRate < 1)
			this->zoomRate += 0.2;
		else
			return;
	}
	else {
		if (this->zoomRate > 2)
			this->zoomRate--;
		else if (this->zoomRate <= 2 && this->zoomRate > 1)
			this->zoomRate -= 0.5;
		else if (this->zoomRate <= 1 && math::compare(this->zoomRate, 0.2) == 1)
			this->zoomRate -= 0.2;
		else if ((math::compare(this->zoomRate, 0.2) == 0 || math::compare(this->zoomRate, 0.2) == -1) &&
			math::compare(this->zoomRate, 0.05) == 1)
			this->zoomRate -= 0.01;
		else
			return;
	}


	this->scroll.vertical = (-1 * (this->zoomRate*this->coordinate.y) -
		event->y() + (this->axis.getCenter().y*this->zoomRate));
	this->scroll.horizontal = (this->zoomRate*this->coordinate.x -
		event->x() + (this->axis.getCenter().x*this->zoomRate));

	this->widget->update();
	this->widget->captureImage();

	ShZoomRateChangedEvent notifyEvent(this->zoomRate);
	this->widget->notify(&notifyEvent);
}

void ShCADWidgetImp::shiftViewport(const ShPoint3d &coordinate, int dx, int dy) {

	this->coordinate = coordinate;

	this->scroll.vertical = (-1 * (this->zoomRate*this->coordinate.y) - dy +
		(this->axis.getCenter().y*this->zoomRate));
	this->scroll.horizontal = (this->zoomRate*this->coordinate.x - dx +
		(this->axis.getCenter().x*this->zoomRate));

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();

	QPoint pos = this->widget->mapFromGlobal(QCursor::pos());
	this->convertDeviceToEntity(pos.x(), pos.y(), this->coordinate.x, this->coordinate.y);

	ShMousePositionChangedEvent notifyEvent(this->coordinate);
	this->widget->notify(&notifyEvent);
}

void ShCADWidgetImp::plot(QPainter *painter, double scale) {

	ShPloter visitor(this->widget, painter, scale);

	auto itr = this->entityTable->turnOnLayerBegin();

	for (itr; itr != this->entityTable->turnOnLayerEnd(); ++itr)
		(*itr)->accept(&visitor);
}

ShLayer* ShCADWidgetImp::getCurrentLayer() const {

	return this->layerTable->getCurrentLayer();
}


QCursor ShCADWidgetImp::getCursorShape() const {

	return this->actionHandlerProxy->getCursorShape();
}

ActionType ShCADWidgetImp::getCurrentActionType() const {

	return this->actionHandlerProxy->getType();
}