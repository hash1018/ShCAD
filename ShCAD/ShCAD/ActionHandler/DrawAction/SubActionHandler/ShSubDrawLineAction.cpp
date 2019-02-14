

#include "ShSubDrawLineAction.h"
#include <QMouseEvent>
#include "Entity\Leaf\ShLine.h"
ShSubDrawLineAction::ShSubDrawLineAction(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:drawLineAction(drawLineAction), view(view) {

}

ShSubDrawLineAction::ShSubDrawLineAction(const ShSubDrawLineAction& other)
	: drawLineAction(other.drawLineAction), view(other.view) {

}

ShSubDrawLineAction::~ShSubDrawLineAction() {

}

////////////////////////////////////////////////////////////////////////

ShDrawLineMethod::ShDrawLineMethod(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:ShSubDrawLineAction(drawLineAction, view) {

}

ShDrawLineMethod::ShDrawLineMethod(const ShDrawLineMethod& other)
	: ShSubDrawLineAction(other.drawLineAction, other.view) {

}


ShDrawLineMethod::~ShDrawLineMethod() {

}


////////////////////////////////////////////////////////////////////////////////////////////

ShDrawLineMethod_Default::ShDrawLineMethod_Default(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:ShDrawLineMethod(drawLineAction, view) {

}

ShDrawLineMethod_Default::ShDrawLineMethod_Default(const ShDrawLineMethod_Default& other)
	: ShDrawLineMethod(other) {

}


ShDrawLineMethod_Default::~ShDrawLineMethod_Default() {

}

void ShDrawLineMethod_Default::MousePressEvent(QMouseEvent *event) {


	ShPoint3d& start = this->GetStart();
	ShPoint3d& end = this->GetEnd();
	ShDrawLineAction::Status& status = this->GetStatus();

	ShPoint3d cursor;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), cursor.x, cursor.y);

	if (status == ShDrawLineAction::PickedNothing) {

		start = this->point;
		status = ShDrawLineAction::PickedStart;

		this->view->preview.Add(new ShLine(ShPropertyData(*this->view->GetData()->GetPropertyData()),
			ShLineData(start, cursor), this->view->entityTable.GetLayerTable()->GetCurrentLayer()));

		this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

	}
	else {

		end = this->point;
		ShLineData data(start, end);

		dynamic_cast<ShLine*>((*this->view->preview.Begin()))->SetData(data);

		this->AddEntity((*this->view->preview.Begin())->Clone(), "Line");

		start = end;

		data = ShLineData(start, cursor);
		dynamic_cast<ShLine*>((*this->view->preview.Begin()))->SetData(data);
	}

}


void ShDrawLineMethod_Default::MouseMoveEvent(QMouseEvent *event, DrawType& drawType) {

	ShPoint3d start = this->GetStart();
	ShPoint3d end = this->GetEnd();
	ShDrawLineAction::Status status = this->GetStatus();

	if (status == ShDrawLineAction::PickedStart) {
		this->view->ConvertDeviceToEntity(event->x(), event->y(),
			end.x, end.y);

		ShLineData data(start, end);

		dynamic_cast<ShLine*>((*this->view->preview.Begin()))->SetData(data);

		//this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		drawType = (DrawType)(drawType | DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities);
	}


}


void ShDrawLineMethod_Default::Decorate(ShDrawLineDecorator *drawLineDecorator) {

	drawLineDecorator->SetSubAction(new ShDrawLineMethod_Default(*this));
	this->drawLineAction->ChangeSubAction(drawLineDecorator);

}



///////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawLineDecorator::ShDrawLineDecorator(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:ShSubDrawLineAction(drawLineAction, view), subDrawLineAction(0) {

}

ShDrawLineDecorator::ShDrawLineDecorator(ShDrawLineAction *drawLineAction, ShGraphicView *view,
	ShSubDrawLineAction *subDrawLineAction)
	:ShSubDrawLineAction(drawLineAction, view), subDrawLineAction(subDrawLineAction) {

}

ShDrawLineDecorator::ShDrawLineDecorator(const ShDrawLineDecorator& other)
	: ShSubDrawLineAction(other), subDrawLineAction(other.subDrawLineAction) {

}

ShDrawLineDecorator::~ShDrawLineDecorator() {

	if (this->subDrawLineAction != 0)
		delete this->subDrawLineAction;

}

void ShDrawLineDecorator::SetSubAction(ShSubDrawLineAction *subAction) {

	if (this->subDrawLineAction != 0)
		delete this->subDrawLineAction;

	this->subDrawLineAction = subAction;
}

void ShDrawLineDecorator::TakeOffBoundarySubAction() {

	ShSubDrawLineAction *current = this->subDrawLineAction;
	this->subDrawLineAction = 0;
	this->drawLineAction->ChangeSubAction(current);
}



////////////////////////////////////////////////////////////////////////////////
#include "State Pattern\ShObjectSnapContext.h"
ShDrawLineDecorator_SnapMode::ShDrawLineDecorator_SnapMode(ShDrawLineAction *drawLineAction, ShGraphicView *view,
	ObjectSnap objectSnap)
	:ShDrawLineDecorator(drawLineAction, view), objectSnap(objectSnap) {
	
	this->objectSnapContext = new ShObjectSnapContext(this->view, this->objectSnap);

}


ShDrawLineDecorator_SnapMode::ShDrawLineDecorator_SnapMode(ShDrawLineAction *drawLineAction, ShGraphicView *view,
	ShDrawLineMethod *subDrawLineAction, ObjectSnap objectSnap)
	:ShDrawLineDecorator(drawLineAction, view, subDrawLineAction), objectSnap(objectSnap) {

	this->objectSnapContext = new ShObjectSnapContext(this->view, this->objectSnap);
}

ShDrawLineDecorator_SnapMode::ShDrawLineDecorator_SnapMode(const ShDrawLineDecorator_SnapMode& other)
	: ShDrawLineDecorator(other),objectSnap(other.objectSnap) {

	this->objectSnapContext = new ShObjectSnapContext(this->view, this->objectSnap);
}

ShDrawLineDecorator_SnapMode::~ShDrawLineDecorator_SnapMode() {

	if (this->objectSnapContext != 0)
		delete this->objectSnapContext;
}

void ShDrawLineDecorator_SnapMode::MousePressEvent(QMouseEvent *event) {

	if (this->subDrawLineAction == 0) {
		qDebug("subDrawLineAction is a null pointer.");
		return;
	}

	if (this->objectSnapContext->FindSnapPoint(event) == false) {


		return;
	}

	

	ShPoint3d point;
	point.x = this->objectSnapContext->GetSnapX();
	point.y = this->objectSnapContext->GetSnapY();
	this->subDrawLineAction->SetPoint(point);
	this->subDrawLineAction->MousePressEvent(event);


	
	this->TakeOffBoundarySubAction();



}

void ShDrawLineDecorator_SnapMode::MouseMoveEvent(QMouseEvent *event, DrawType& drawType) {
	
	if (this->subDrawLineAction == 0) {
		qDebug("subDrawLineAction is a null pointer.");
		return;
	}

	if(this->objectSnapContext->FindSnapPoint(event)==true)
		drawType = (DrawType)(drawType | DrawType::DrawActionHandler | DrawType::DrawCaptureImage);

	
	this->subDrawLineAction->MouseMoveEvent(event, drawType);
}

void ShDrawLineDecorator_SnapMode::Draw(QPainter *painter) {

	this->objectSnapContext->Draw(painter);
}

void ShDrawLineDecorator_SnapMode::Decorate(ShDrawLineDecorator *drawLineDecorator) {

	if (drawLineDecorator == 0) {
		qDebug("variable is a null pointer.");
		return;
	}

	if (dynamic_cast<ShDrawLineDecorator_SnapMode*>(drawLineDecorator)) {
		
		delete drawLineDecorator;
		this->TakeOffBoundarySubAction();
	}
	
	
}