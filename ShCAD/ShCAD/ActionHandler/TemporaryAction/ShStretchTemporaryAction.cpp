

#include "ShStretchTemporaryAction.h"
#include <QKeyEvent>
#include "ShNotifyEvent.h"
#include "Entity\Composite\ShPreview.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "Interface\ShGraphicView.h"


ShStretchTemporaryAction::ShStretchTemporaryAction(ShGraphicView *graphicView
	,const QLinkedList<ShEntity*>& list, const QLinkedList<HitPoint>& hitList, ShPoint3d vertex)
	:ShTemporaryAction(graphicView), list(list), hitList(hitList), vertex(vertex) {

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		this->graphicView->preview.Add((*itr)->Clone());
	
	if (this->graphicView->rubberBand != 0)
		delete this->graphicView->rubberBand;

	ShPoint3d point(vertex.x, vertex.y);
	this->graphicView->rubberBand = new ShRubberBand(ShLineData(point, point));

	this->graphicView->update((DrawType)(DrawType::DrawCaptureImage |
		DrawType::DrawPreviewEntities | DrawType::DrawActionHandler));

	qDebug("Changed to StretchTemporaryAction.");
}

ShStretchTemporaryAction::~ShStretchTemporaryAction() {

	
	this->graphicView->preview.DeleteAll();

	if (this->graphicView->rubberBand != 0) {
		delete this->graphicView->rubberBand;
		this->graphicView->rubberBand = 0;
	}

	this->graphicView->update(DrawType::DrawCaptureImage);
	
}


#include "Command Pattern\Entity Command\ShStretchEntityCommand.h"
void ShStretchTemporaryAction::MousePressEvent(QMouseEvent *event, ShActionData& data) {

	ShPoint3d point;
	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);
	
	ShStretchEntityCommand *command = new ShStretchEntityCommand(this->graphicView,
		this->list, this->hitList, this->vertex, point);

	command->Execute();

	this->graphicView->undoTaker.Push(command);

	if (!this->graphicView->redoTaker.IsEmpty())
		this->graphicView->redoTaker.DeleteAll();
	
	this->ReturnToPrevious();

}


#include "Visitor Pattern\ShStretchVisitor.h"
void ShStretchTemporaryAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	ShPoint3d end;
	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), end.x, end.y);
	this->graphicView->rubberBand->SetEnd(end);

	ShStretchVisitor visitor(end.x, end.y);

	QLinkedList<ShEntity*>::iterator itr;
	QLinkedList<HitPoint>::iterator itrHitPoint = this->hitList.begin();
	QLinkedList<ShEntity*>::iterator originalItr = this->list.begin();

	for (itr = this->graphicView->preview.Begin();
		itr != this->graphicView->preview.End();
		++itr) {

		visitor.SetHitPoint((*itrHitPoint));
		visitor.SetOrigianlEntity((*originalItr));

		++originalItr;
		++itrHitPoint;
		(*itr)->Accept(&visitor);
	}

	data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage |
			DrawType::DrawPreviewEntities | DrawType::DrawActionHandler));
}

void ShStretchTemporaryAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {
	
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

QCursor ShStretchTemporaryAction::GetCursorShape() {
	
	return QCursor(Qt::CursorShape::CrossCursor);
}

ActionType ShStretchTemporaryAction::GetType() {

	return ActionType::ActionSelectionMove;
}

#include <qpainter.h>
void ShStretchTemporaryAction::DrawVertex() {

	int dx, dy;
	this->graphicView->ConvertEntityToDevice(this->vertex.x, this->vertex.y, dx, dy);

	QPainter painter(this->graphicView);
	painter.fillRect(dx - 3, dy - 3, 6, 6, QColor(255, 000, 000));
}

void ShStretchTemporaryAction::EraseVertex() {

	int dx, dy;
	this->graphicView->ConvertEntityToDevice(this->vertex.x, this->vertex.y, dx, dy);

	QPainter painter(this->graphicView);
	painter.fillRect(dx - 3, dy - 3, 6, 6, QColor(000, 153, 255));

}

void ShStretchTemporaryAction::Draw(QPainter *painter) {

	if (painter->isActive() == false)
		painter->begin(this->graphicView);


	int dx, dy;
	this->graphicView->ConvertEntityToDevice(this->vertex.x, this->vertex.y, dx, dy);

	painter->fillRect(dx - 3, dy - 3, 6, 6, QColor(255, 000, 000));

}