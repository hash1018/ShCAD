
#include "ShPlotAreaSelectAction.h"
#include <QKeyEvent>
#include "ShNotifyEvent.h"
#include "Interface\Dialog\ShPlotDialog.h"
#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
ShPlotAreaSelectAction::ShPlotAreaSelectAction(ShGraphicView *graphicView)
	:ShActionHandler(graphicView), status(PickedNothing) {

	ShUpdateCommandEditHeadTitle event(this->GetActionHeadTitle());
	this->graphicView->Notify(&event);
}

ShPlotAreaSelectAction::~ShPlotAreaSelectAction() {

	this->plotDialog->setVisible(true);
}

void ShPlotAreaSelectAction::LMousePressEvent(QMouseEvent *event, ShActionData& data) {

	if (this->status == PickedNothing) {

		this->firstX = data.GetPoint().x;
		this->firstY = data.GetPoint().y;

		this->status = PickedFirstPoint;

		ShUpdateListTextEvent event2("");
		this->graphicView->Notify(&event2);

		ShUpdateCommandEditHeadTitle event3(this->GetActionHeadTitle());
		this->graphicView->Notify(&event3);
	}
	else if (this->status == PickedFirstPoint) {
	
		this->plotDialog->SetWindowPrevXY(this->firstX, this->firstY);
		this->plotDialog->SetWindowCurrentXY(this->secondX, this->secondY);

		ShChangeCurrentActionCurrentFinished strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);
		
	}
}


void ShPlotAreaSelectAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	if (this->status == PickedFirstPoint) {
	
		this->secondX = data.GetPoint().x;
		this->secondY = data.GetPoint().y;

		data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawActionHandler));
	}
}


void ShPlotAreaSelectAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {

	if (event->key() == Qt::Key::Key_Escape) {

		ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);

	}
	else {

		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
}


ActionType ShPlotAreaSelectAction::GetType() {

	return ActionType::ActionPlotAreaSelect;
}

QCursor ShPlotAreaSelectAction::GetCursorShape() {

	return QCursor(Qt::CursorShape::DragCopyCursor);
}

#include <qpainter.h>
void ShPlotAreaSelectAction::Draw(QPainter *painter) {

	if (painter->isActive() == false)
		painter->begin(this->graphicView);

	int firstX, firstY, secondX, secondY;
	this->graphicView->ConvertEntityToDevice(this->firstX, this->firstY, firstX, firstY);
	this->graphicView->ConvertEntityToDevice(this->secondX, this->secondY, secondX, secondY);

	int width = abs(firstX - secondX);
	int height = abs(firstY - secondY);

	QPen oldPen = painter->pen();

	QPen pen;
	pen.setColor(QColor(255, 255, 255));
	painter->setPen(pen);

	pen.setStyle(Qt::PenStyle::DotLine);
	painter->setPen(pen);
	if (firstX <= secondX) {

		if (firstY >= secondY) {
			painter->drawRect(firstX, firstY - height, width, height);
		}
		else {
			painter->drawRect(firstX, firstY, width, height);
		}

	}
	else {

		if (firstY >= secondY) {
			painter->drawRect(secondX, secondY, width, height);
		}
		else {
			painter->drawRect(secondX, firstY, width, height);
		}
	}

	painter->setPen(oldPen);
	painter->end();
}

QString ShPlotAreaSelectAction::GetActionHeadTitle() {

	QString str;

	if (this->status == PickedNothing)
		str = "Plot >> Specify first corner: ";
	else if (this->status == PickedFirstPoint)
		str = "Plot >> Specify opposite corner: ";

	return str;
}