

#include "ShSubDefaultAction.h"
#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"
#include "ActionHandler\ShDefaultAction.h"
#include <QMouseEvent>
ShSubDefaultAction::ShSubDefaultAction(ShDefaultAction *defaultAction, ShGraphicView *view)
	:defaultAction(defaultAction), view(view) {

}

ShSubDefaultAction::~ShSubDefaultAction() {

}

///////////////////////////////////////////////////////////////////////////

ShSubDefaultAction_Default::ShSubDefaultAction_Default(ShDefaultAction *defaultAction, ShGraphicView *view)
	:ShSubDefaultAction(defaultAction, view) {

}

ShSubDefaultAction_Default::~ShSubDefaultAction_Default() {

}

void ShSubDefaultAction_Default::MousePressEvent(QMouseEvent *event) {

	ShEntity *entity = this->view->entityTable.FindEntity(this->view->GetX(),
		this->view->GetY(), this->view->GetZoomRate());

	if (entity == NULL) {

		double firstX, firstY;
		this->view->ConvertDeviceToEntity(event->x(), event->y(), firstX, firstY);
		this->view->SetTemporaryAction(new ShDragSelectAction(this->view, this->defaultAction, firstX, firstY));
		return;
	}

	if (event->modifiers() == Qt::ShiftModifier) {
		if (this->view->selectedEntityManager.Pop(entity) == true) {
			this->view->update(DrawType::DrawAll);
			this->view->CaptureImage();
		}
	}
	else {
		if (this->view->selectedEntityManager.Push(entity) == true) {
			this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
			this->view->CaptureImage();
		}
	}

}

#include "Visitor Pattern\ShHitTester.h"
void ShSubDefaultAction_Default::MouseMoveEvent(QMouseEvent *event) {

	double x, y;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), x, y);

	HitPoint hitPoint = HitPoint::HitNothing;

	ShHitTester hitTester(x, y, view->GetZoomRate(), hitPoint);

	QLinkedList<ShEntity*>::iterator itr = this->view->selectedEntityManager.Begin();

	while (itr != this->view->selectedEntityManager.End() &&
		(hitPoint == HitPoint::HitNothing || hitPoint == HitPoint::HitOther)) {
	
		(*itr)->Accept(&hitTester);
		++itr;
	}


	if (hitPoint != HitPoint::HitNothing && hitPoint != HitPoint::HitOther) {
		
		--itr;
		ShPoint3d vertex;
		(*itr)->GetHitPoint(hitPoint, vertex);
		
		//Set Cursor to vertex.
		int dx, dy;
		this->view->ConvertEntityToDevice(vertex.x, vertex.y, dx, dy);
		QCursor::setPos(this->view->mapToGlobal(QPoint(dx, dy)));


		ShSubDefaultAction_MouseIsInEntityVertex *subAction =
			new ShSubDefaultAction_MouseIsInEntityVertex(this->defaultAction, this->view, vertex);
		
		this->defaultAction->ChangeSubAction(subAction);

	}

}


//////////////////////////////////////////////////////////////////////////

ShSubDefaultAction_MouseIsInEntityVertex::ShSubDefaultAction_MouseIsInEntityVertex(ShDefaultAction *defaultAction,
	ShGraphicView *view, const ShPoint3d& vertex)
	:ShSubDefaultAction(defaultAction, view), vertex(vertex) {

	this->DrawVertex();
}

ShSubDefaultAction_MouseIsInEntityVertex::~ShSubDefaultAction_MouseIsInEntityVertex() {

	this->EraseVertex();
}


#include "ActionHandler\TemporaryAction\ShStretchTemporaryAction.h"
void ShSubDefaultAction_MouseIsInEntityVertex::MousePressEvent(QMouseEvent *event) {
	//Change to SelectionMove.

	HitPoint hitPoint = HitPoint::HitNothing;
	ShHitTester hitTester(this->vertex.x, this->vertex.y, this->view->GetZoomRate(), hitPoint);

	QLinkedList<ShEntity*> list;
	QLinkedList<HitPoint> hitList;

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->view->selectedEntityManager.Begin();
		itr != this->view->selectedEntityManager.End();
		++itr) {
	
		(*itr)->Accept(&hitTester);

		if (hitPoint != HitPoint::HitNothing && hitPoint != HitPoint::HitOther) {
			list.append((*itr));
			hitList.append(hitPoint);
		}
	}

	ShStretchTemporaryAction *action = new ShStretchTemporaryAction(this->view, this->defaultAction,
		list, hitList, this->vertex);
	this->view->SetTemporaryAction(action);
	
	this->defaultAction->ChangeSubAction(new ShSubDefaultAction_Default(this->defaultAction, this->view));



}

#include "ShMath.h"
void ShSubDefaultAction_MouseIsInEntityVertex::MouseMoveEvent(QMouseEvent *event) {

	ShPoint3d point;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);

	ShPoint3d topLeft, bottomRight;
	int dx, dy;
	this->view->ConvertEntityToDevice(this->vertex.x, this->vertex.y, dx, dy);

	this->view->ConvertDeviceToEntity(dx - 3, dy - 3, topLeft.x, topLeft.y);
	this->view->ConvertDeviceToEntity(dx + 3, dy + 3, bottomRight.x, bottomRight.y);

	

	if (Math::CheckPointLiesInsideRect(point, topLeft, bottomRight, 1) == false) {
	
		this->defaultAction->ChangeSubAction(new ShSubDefaultAction_Default(this->defaultAction, this->view));
	}


}

#include <qpainter.h>
void ShSubDefaultAction_MouseIsInEntityVertex::DrawVertex() {

	int dx, dy;
	this->view->ConvertEntityToDevice(this->vertex.x, this->vertex.y, dx, dy);

	QPainter painter(this->view);
	painter.fillRect(dx - 3, dy - 3, 6, 6, QColor(255, 000, 000));

}

void ShSubDefaultAction_MouseIsInEntityVertex::EraseVertex() {

	int dx, dy;
	this->view->ConvertEntityToDevice(this->vertex.x, this->vertex.y, dx, dy);

	QPainter painter(this->view);
	painter.fillRect(dx - 3, dy - 3, 6, 6, QColor(000, 153, 255));

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////