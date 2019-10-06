
#include "ShCADWidget.h"
#include "Interface\Private\ShCADWidgetImp.h"
#include "Manager\ShCADWidgetManager.h"
#include "Event\ShNotifyEvent.h"
#include "Manager\ShChangeManager.h"
#include "Event\ShCADWidgetEventFilter.h"

ShCADWidget::ShCADWidget(QWidget *parent)
	:QOpenGLWidget(parent), widgetImp(nullptr) {

	this->widgetImp = new ShCADWidgetImp(this);
	this->widgetImp->init();

	this->setCursor(this->widgetImp->getCursorShape());
	this->setFocusPolicy(Qt::FocusPolicy::WheelFocus);
}

ShCADWidget::~ShCADWidget() {

	if (this->widgetImp != nullptr)
		delete this->widgetImp;

	ShCADWidgetManager::getInstance()->remove(this);
}


void ShCADWidget::initializeGL() {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	this->captureImage();
}


void ShCADWidget::resizeGL(int width, int height) {

	QOpenGLWidget::resizeGL(width, height);
	this->update();
	this->captureImage();
}

void ShCADWidget::paintGL() {
	
	this->widgetImp->paintGL();
}


void ShCADWidget::mousePressEvent(QMouseEvent *event) {

	this->widgetImp->mousePressEvent(event);
}

void ShCADWidget::mouseMoveEvent(QMouseEvent *event) {

	if (this->hasFocus() == false)
		this->setFocus();

	this->widgetImp->mouseMoveEvent(event);
}

void ShCADWidget::mouseReleaseEvent(QMouseEvent *event) {

	this->widgetImp->mouseReleaseEvent(event);
}

void ShCADWidget::keyPressEvent(QKeyEvent *event) {
	
	this->widgetImp->keyPressEvent(event);
}

void ShCADWidget::wheelEvent(QWheelEvent *event) {

	this->widgetImp->wheelEvent(event);
}

void ShCADWidget::focusInEvent(QFocusEvent *event) {

	ShCADWidgetManager *manager = ShCADWidgetManager::getInstance();

	if (manager->getActivatedWidget() == this)
		return;

	ShActivatedWidgetChangedEvent notifyEvent(this, manager->getActivatedWidget());
	this->notify(&notifyEvent);

	manager->setActivatedWidget(this);
}



void ShCADWidget::notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::getInstance();

	manager->notify(this, event);
}

void ShCADWidget::update(ShNotifyEvent *event) {

	ShCADWidgetEventFilter filter(this, event);
	filter.update();
}


void ShCADWidget::update(DrawType drawType) {
	
	if (this->drawBuffer.saveToBuffer == true) {
		this->drawBuffer.buffer = (DrawType)(this->drawBuffer.buffer | drawType);
	}
	else {
		this->drawBuffer.drawType = drawType;
		QOpenGLWidget::update();
	}
}

void ShCADWidget::changeAction(ShChangeActionStrategy &strategy) {

	this->widgetImp->changeAction(strategy);
}

void ShCADWidget::convertDeviceToEntity(const int &x, const int &y, double &ex, double &ey) {

	this->widgetImp->convertDeviceToEntity(x, y, ex, ey);
}

void ShCADWidget::convertEntityToDevice(const double &x, const double &y, int &dx, int &dy) {

	this->widgetImp->convertEntityToDevice(x, y, dx, dy);
}

void ShCADWidget::captureImage() {
	
	this->capturedImage = this->grabFramebuffer();
}

void ShCADWidget::shiftViewport(const ShPoint3d &coordinate, int dx, int dy) {

	this->widgetImp->shiftViewport(coordinate, dx, dy);
}

ShPoint3d ShCADWidget::getMousePoint() {

	ShPoint3d mouse;
	QPoint pos = this->mapFromGlobal(QCursor::pos());
	this->widgetImp->convertDeviceToEntity(pos.x(), pos.y(), mouse.x, mouse.y);

	return mouse;
}

void ShCADWidget::plot(QPainter *painter, double scale) {

	this->widgetImp->plot(painter, scale);
}

void ShCADWidget::setCoordinate(const ShPoint3d &coordinate) {

	this->widgetImp->setCoordinate(coordinate);
}

void ShCADWidget::setScrollPosition(const ShScrollPosition &scrollPosition) {

	this->widgetImp->setScrollPosition(scrollPosition);
}

void ShCADWidget::setZoomRate(const double &zoomRate) {

	this->widgetImp->setZoomRate(zoomRate);
}

void ShCADWidget::setPropertyData(const ShPropertyData &data) {

	this->widgetImp->setPropertyData(data);
}

void ShCADWidget::setLastBasePoint(const ShPoint3d &point) {

	this->widgetImp->setLastBasePoint(point);
}

ShLayer* ShCADWidget::getCurrentLayer() const {

	return this->widgetImp->getCurrentLayer();
}

const ShPoint3d& ShCADWidget::getCoordinate() const {

	return this->widgetImp->getCoordinate();
}

const ShScrollPosition& ShCADWidget::getScrollPosition() const {

	return this->widgetImp->getScrollPosition();
}

const double& ShCADWidget::getZoomRate() const {

	return this->widgetImp->getZoomRate();
}

ShAxis& ShCADWidget::getAxis() const {

	return this->widgetImp->getAxis();
}

ShActionHandlerProxy* ShCADWidget::getActionHandlerProxy() const {

	return this->widgetImp->getActionHandlerProxy();
}

ShTransactionStack* ShCADWidget::getRedoStack() const {

	return this->widgetImp->getRedoStack();
}

ShTransactionStack* ShCADWidget::getUndoStack() const {

	return this->widgetImp->getUndoStack();
}

ShCommandLog& ShCADWidget::getCommandLog() const {

	return this->widgetImp->getCommandLog();
}

ShRubberBand& ShCADWidget::getRubberBand() const {

	return this->widgetImp->getRubberBand();
}

ShEntityTable& ShCADWidget::getEntityTable() const {

	return this->widgetImp->getEntityTable();
}

ShPreview& ShCADWidget::getPreview() const {

	return this->widgetImp->getPreview();
}

ShDraftData& ShCADWidget::getDraftData() {

	return this->widgetImp->getDraftData();
}

const ShPropertyData& ShCADWidget::getPropertyData() const {

	return this->widgetImp->getPropertyData();
}

ShLayerTable* ShCADWidget::getLayerTable() const {

	return this->widgetImp->getLayerTable();
}

ShSelectedEntities* ShCADWidget::getSelectedEntities() const {

	return this->widgetImp->getSelectedEntities();
}

ActionType ShCADWidget::getCurrentActionType() const {

	return this->widgetImp->getCurrentActionType();
}

ShPointStyle& ShCADWidget::getPointStyle() const {

	return this->widgetImp->getPointStyle();
}

const ShPoint3d& ShCADWidget::getLastBasePoint() const {

	return this->widgetImp->getLastBasePoint();
}

ShActionHandler* ShCADWidget::getCurrentAction() const {

	return this->widgetImp->getCurrentAction();
}