

#include "ShSelectionMoveAction.h"
#include <QKeyEvent>
#include "ShNotifyEvent.h"
#include "Entity\Composite\ShPreview.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "Interface\ShGraphicView.h"
ShSelectionMoveAction::ShSelectionMoveAction(ShGraphicView *graphicView, ShActionHandler *previousAction,
	const QLinkedList<ShEntity*>& list, const QLinkedList<HitPoint>& hitList, ShPoint3d vertex)
	:ShTemporaryAction(graphicView, previousAction), list(list), hitList(hitList), vertex(vertex) {

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		this->graphicView->preview.Add((*itr)->Clone());
	
	if (this->graphicView->rubberBand != 0)
		delete this->graphicView->rubberBand;

	ShPoint3d point(vertex.x, vertex.y);
	this->graphicView->rubberBand = new ShRubberBand(ShLineData(point, point));

	this->graphicView->update((DrawType)(DrawType::DrawCaptureImage |
		DrawType::DrawPreviewEntities | DrawType::DrawActionHandler));

	qDebug("Changed to SelectionMoveAction.");
}

ShSelectionMoveAction::~ShSelectionMoveAction() {

	
	this->graphicView->preview.DeleteAll();

	if (this->graphicView->rubberBand != 0) {
		delete this->graphicView->rubberBand;
		this->graphicView->rubberBand = 0;
	}

	this->graphicView->update(DrawType::DrawCaptureImage);
	
}

#include "Visitor Pattern\ShSelectionMover.h"
void ShSelectionMoveAction::MousePressEvent(QMouseEvent *event) {

	ShPoint3d point;
	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);
	

	ShSelectionMover selectionMover(point.x, point.y);

	QLinkedList<ShEntity*>::iterator itr;
	QLinkedList<HitPoint>::iterator itrHitPoint = this->hitList.begin();

	for (itr = this->list.begin(); itr != this->list.end(); ++itr) {

		selectionMover.SetHitPoint((*itrHitPoint));
		++itrHitPoint;
		(*itr)->Accept(&selectionMover);
	}

	this->graphicView->update(DrawType::DrawAll);
	this->graphicView->CaptureImage();



	this->ReturnToPrevious();


}


void ShSelectionMoveAction::MouseMoveEvent(QMouseEvent *event) {

	ShPoint3d end;
	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), end.x, end.y);
	this->graphicView->rubberBand->SetEnd(end);

	ShSelectionMover selectionMover(end.x, end.y);

	QLinkedList<ShEntity*>::iterator itr;
	QLinkedList<HitPoint>::iterator itrHitPoint = this->hitList.begin();

	for (itr = this->graphicView->preview.Begin();
		itr != this->graphicView->preview.End();
		++itr) {

		selectionMover.SetHitPoint((*itrHitPoint));
		++itrHitPoint;
		(*itr)->Accept(&selectionMover);
	}


	this->graphicView->update((DrawType)(DrawType::DrawCaptureImage |
		DrawType::DrawPreviewEntities | DrawType::DrawActionHandler));
}

void ShSelectionMoveAction::KeyPressEvent(QKeyEvent *event) {
	
	if (event->key() == Qt::Key::Key_Escape) {

		this->ReturnToPrevious();
		
		ShUpdateListTextEvent event("<Cancel>");
		this->graphicView->Notify(&event);
	}
	else {

		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
}

QCursor ShSelectionMoveAction::GetCursorShape() {
	
	return QCursor(Qt::CursorShape::CrossCursor);
}

ActionType ShSelectionMoveAction::GetType() {

	return ActionType::ActionSelectionMove;
}

#include <qpainter.h>
void ShSelectionMoveAction::DrawVertex() {

	int dx, dy;
	this->graphicView->ConvertEntityToDevice(this->vertex.x, this->vertex.y, dx, dy);

	QPainter painter(this->graphicView);
	painter.fillRect(dx - 3, dy - 3, 6, 6, QColor(255, 000, 000));
}

void ShSelectionMoveAction::EraseVertex() {

	int dx, dy;
	this->graphicView->ConvertEntityToDevice(this->vertex.x, this->vertex.y, dx, dy);

	QPainter painter(this->graphicView);
	painter.fillRect(dx - 3, dy - 3, 6, 6, QColor(000, 153, 255));

}

void ShSelectionMoveAction::Draw(QPainter *painter) {

	if (painter->isActive() == false)
		painter->begin(this->graphicView);


	int dx, dy;
	this->graphicView->ConvertEntityToDevice(this->vertex.x, this->vertex.y, dx, dy);

	painter->fillRect(dx - 3, dy - 3, 6, 6, QColor(255, 000, 000));

}