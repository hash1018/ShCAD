

#include "ShSubDrawLineAction.h"
#include "ActionHandler\DrawAction\ShDrawLineAction.h"
#include <QMouseEvent>
#include "Entity\Leaf\ShLine.h"
ShSubDrawLineAction::ShSubDrawLineAction(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:drawLineAction(drawLineAction), view(view) {

}

ShSubDrawLineAction::~ShSubDrawLineAction() {

}

////////////////////////////////////////////////////////////////////////

ShSubDrawLineAction_Default::ShSubDrawLineAction_Default(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:ShSubDrawLineAction(drawLineAction, view) {

}

ShSubDrawLineAction_Default::~ShSubDrawLineAction_Default() {

}

void ShSubDrawLineAction_Default::MousePressEvent(QMouseEvent *event) {

	if (this->drawLineAction->status == ShDrawLineAction::PickedNothing) {

		this->view->ConvertDeviceToEntity(event->x(), event->y(),
			this->drawLineAction->start.x, this->drawLineAction->start.y);
		this->drawLineAction->status = ShDrawLineAction::PickedStart;

		this->view->preview.Add(new ShLine(ShPropertyData(*this->view->GetData()->GetPropertyData()),
			ShLineData(this->drawLineAction->start, this->drawLineAction->start), this->view->entityTable.GetLayerTable()->GetCurrentLayer()));

		this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

	}
	else {

		this->view->ConvertDeviceToEntity(event->x(), event->y(), this->drawLineAction->end.x, this->drawLineAction->end.y);
		ShLineData data(this->drawLineAction->start, this->drawLineAction->end);

		dynamic_cast<ShLine*>((*this->view->preview.Begin()))->SetData(data);

		this->drawLineAction->AddEntity((*this->view->preview.Begin())->Clone(), "Line");

		this->drawLineAction->start = this->drawLineAction->end;


	}
}

void ShSubDrawLineAction_Default::MouseMoveEvent(QMouseEvent *event) {

	if (this->drawLineAction->status == ShDrawLineAction::PickedStart) {
		this->view->ConvertDeviceToEntity(event->x(), event->y(),
			this->drawLineAction->end.x, this->drawLineAction->end.y);

		ShLineData data(this->drawLineAction->start, this->drawLineAction->end);

		dynamic_cast<ShLine*>((*this->view->preview.Begin()))->SetData(data);

		this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}


}