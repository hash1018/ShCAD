
#include "ShDisposableExtensionSnapAction.h"
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity\Private\ShFinder.h"
#include "Entity\Private\ShSnapPointFinder.h"


ShExtensionBaseData::ShExtensionBaseData() {

}

ShExtensionBaseData::~ShExtensionBaseData() {

}

ShExtensionBaseData& ShExtensionBaseData::operator=(const ShExtensionBaseData &other) {

	this->baseEntities = other.baseEntities;
	this->point = other.point;

	return *this;
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
		if (this->search(data.point) == true)
			this->widget->update((DrawType)(DrawType::DrawActionHandler | DrawType::DrawCaptureImage));
		else
			this->widget->update((DrawType)DrawType::DrawCaptureImage);
	}


	ShDisposableSnapAction::mouseMoveEvent(data);
}

void ShDisposableExtensionSnapAction::draw(QPainter *painter) {

}

void ShDisposableExtensionSnapAction::invalidate(ShDecoratorActionData &data) {

}

bool ShDisposableExtensionSnapAction::search(const ShPoint3d &point) {

	QLinkedList<ShEntity*> foundEntities;

	ShSearchEntityDuplicateStrategy strategy(foundEntities, 10, point.x, point.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);

	if (foundEntities.count() == 0)
		return false;

	VertexType vertexType;
	ShPoint3d vertexPoint;
	ShNearestVertexFinder visitor(point.x, point.y, this->widget->getZoomRate(), vertexType, vertexPoint);

	auto itr = foundEntities.begin();
	for (itr; itr != foundEntities.end(); ++itr) {
	
		(*itr)->accept(&visitor);

		if (vertexType == VertexType::VertexEnd)
			break;
	}

	if (vertexType == VertexType::VertexEnd) {
	
		
	}

}