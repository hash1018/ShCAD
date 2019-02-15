

#include "ShSubDrawLineAction.h"
#include <QMouseEvent>
#include "Entity\Leaf\ShLine.h"
ShSubDrawLineAction::ShSubDrawLineAction(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:drawLineAction(drawLineAction), view(view), parent(0) {

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

ShDrawLineMethod_Default* ShDrawLineMethod_Default::Clone() {

	return new ShDrawLineMethod_Default(*this);
}

void ShDrawLineMethod_Default::MousePressEvent(QMouseEvent *event, ShPoint3d point) {

	ShDrawLineAction::Status& status = this->GetStatus();

	ShPoint3d cursor;
	this->view->ConvertDeviceToEntity(event->x(), event->y(), cursor.x, cursor.y);

	if (status == ShDrawLineAction::PickedNothing) {

		status = ShDrawLineAction::PickedStart;

		this->view->preview.Add(new ShLine(ShPropertyData(*this->view->GetData()->GetPropertyData()),
			ShLineData(point, cursor), this->view->entityTable.GetLayerTable()->GetCurrentLayer()));

		this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

	}
	else if (status == ShDrawLineAction::PickedStart) {

		ShLine *prevLine = dynamic_cast<ShLine*>((*this->view->preview.Begin()));
		ShLineData data = prevLine->GetData();
		data.end = point;

		prevLine->SetData(data);

		this->AddEntity(prevLine->Clone(), "Line");

		data = ShLineData(point, cursor);
		prevLine->SetData(data);
	}

}


void ShDrawLineMethod_Default::MouseMoveEvent(QMouseEvent *event, ShPoint3d point, DrawType& drawType) {

	ShDrawLineAction::Status status = this->GetStatus();

	if (status == ShDrawLineAction::PickedStart) {
		ShLine *prevLine = dynamic_cast<ShLine*>((*this->view->preview.Begin()));

		prevLine->SetEnd(point);
	
		drawType = (DrawType)(drawType | DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities);
	}


}


void ShDrawLineMethod_Default::Decorate(ShDrawLineDecorator *drawLineDecorator) {

	drawLineDecorator->SetChild(this->Clone());
	this->drawLineAction->ChangeSubAction(drawLineDecorator);

}



///////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawLineDecorator::ShDrawLineDecorator(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:ShSubDrawLineAction(drawLineAction, view), child(0) {

}


ShDrawLineDecorator::ShDrawLineDecorator(const ShDrawLineDecorator& other)
	: ShSubDrawLineAction(other), child(other.child->Clone()) {

	this->child->SetParent(this);
}

ShDrawLineDecorator::~ShDrawLineDecorator() {

	if (this->child != 0)
		delete this->child;

}

void ShDrawLineDecorator::SetChild(ShSubDrawLineAction *child) {

	if (this->child != 0)
		delete this->child;

	child->SetParent(this);
	this->child = child;
}



////////////////////////////////////////////////////////////////////////////////

#include "FactoryMethod\ShCreatorObjectSnapFactory.h"
#include "State Pattern\ShObjectSnapState.h"
ShDrawLineDecorator_SnapMode::ShDrawLineDecorator_SnapMode(ShDrawLineAction *drawLineAction, ShGraphicView *view,
	ObjectSnap objectSnap)
	:ShDrawLineDecorator(drawLineAction, view), objectSnap(objectSnap) {
	
	this->objectSnapState = ShCreatorObjectSnapFactory::Create(objectSnap, view);

}


ShDrawLineDecorator_SnapMode::ShDrawLineDecorator_SnapMode(const ShDrawLineDecorator_SnapMode& other)
	: ShDrawLineDecorator(other),objectSnap(other.objectSnap) {

	this->objectSnapState = ShCreatorObjectSnapFactory::Create(objectSnap, view);
}

ShDrawLineDecorator_SnapMode::~ShDrawLineDecorator_SnapMode() {

	if (this->objectSnapState != 0)
		delete this->objectSnapState;
}

ShDrawLineDecorator_SnapMode* ShDrawLineDecorator_SnapMode::Clone() {

	return new ShDrawLineDecorator_SnapMode(*this);
}

void ShDrawLineDecorator_SnapMode::MousePressEvent(QMouseEvent *event, ShPoint3d point) {

	if (this->child == 0) {
		qDebug("subDrawLineAction is a null pointer.");
		return;
	}

	if (this->objectSnapState->FindSnapPoint(event) == false) {



		return;
	}

	
	point.x = this->objectSnapState->GetSnapX();
	point.y = this->objectSnapState->GetSnapY();
	this->child->MousePressEvent(event, point);

	if (this->parent == 0)
		this->drawLineAction->ChangeSubAction(this->child->Clone());
	
	else 
		this->parent->SetChild(this->child->Clone());
	
	



}

void ShDrawLineDecorator_SnapMode::MouseMoveEvent(QMouseEvent *event, ShPoint3d point, DrawType& drawType) {
	
	if (this->child == 0) {
		qDebug("subDrawLineAction is a null pointer.");
		return;
	}

	if(this->objectSnapState->FindSnapPoint(event)==true)
		drawType = (DrawType)(drawType | DrawType::DrawActionHandler | DrawType::DrawCaptureImage);

	
	this->child->MouseMoveEvent(event, point, drawType);
}

void ShDrawLineDecorator_SnapMode::Draw(QPainter *painter) {

	this->objectSnapState->Draw(painter);
}

void ShDrawLineDecorator_SnapMode::Decorate(ShDrawLineDecorator *drawLineDecorator) {

	if (drawLineDecorator == 0) {
		qDebug("variable is a null pointer.");
		return;
	}

	if (dynamic_cast<ShDrawLineDecorator_SnapMode*>(drawLineDecorator)) {
		
		delete drawLineDecorator;
		this->drawLineAction->ChangeSubAction(this->child->Clone());
	}
	else {
	
		drawLineDecorator->SetChild(this->Clone());
		this->drawLineAction->ChangeSubAction(drawLineDecorator);
	}
	
	
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawLineDecorator_SnapMode_Perpendicular::ShDrawLineDecorator_SnapMode_Perpendicular(ShDrawLineAction *drawLineAction,
	ShGraphicView *view, ObjectSnap objectSnap)
	:ShDrawLineDecorator_SnapMode(drawLineAction, view, objectSnap) {

}

ShDrawLineDecorator_SnapMode_Perpendicular::ShDrawLineDecorator_SnapMode_Perpendicular
(const ShDrawLineDecorator_SnapMode_Perpendicular& other)
	: ShDrawLineDecorator_SnapMode(other) {

}

ShDrawLineDecorator_SnapMode_Perpendicular::~ShDrawLineDecorator_SnapMode_Perpendicular() {

}

void ShDrawLineDecorator_SnapMode_Perpendicular::MousePressEvent(QMouseEvent *event, ShPoint3d point) {

	if (this->child == 0) {
		qDebug("subDrawLineAction is a null pointer.");
		return;
	}
	
	if (this->GetStatus() == ShDrawLineAction::Status::PickedNothing) {

		if (this->objectSnapState->FindSnapPoint(event) == false) {
		
			return;
		}
		
		//to Do...

	}
	else {
		ShPoint3d start = dynamic_cast<ShLine*>((*this->view->preview.Begin()))->GetStart();
		ShObjectSnapState_Perpendicular *state = dynamic_cast<ShObjectSnapState_Perpendicular*>(this->objectSnapState);

		if (state->FindSnapPoint(event, start.x, start.y) == false) {
		
			return;
		}

		point.x = this->objectSnapState->GetSnapX();
		point.y = this->objectSnapState->GetSnapY();
		this->child->MousePressEvent(event, point);

		if (this->parent == 0)
			this->drawLineAction->ChangeSubAction(this->child->Clone());

		else
			this->parent->SetChild(this->child->Clone());
		

	}

	
}

void ShDrawLineDecorator_SnapMode_Perpendicular::MouseMoveEvent(QMouseEvent *event, ShPoint3d point, DrawType& drawType) {

	if (this->child == 0) {
		qDebug("subDrawLineAction is a null pointer.");
		return;
	}

	if (this->GetStatus() == ShDrawLineAction::Status::PickedNothing) {

		if (this->objectSnapState->FindSnapPoint(event) == true)
			drawType = (DrawType)(drawType | DrawType::DrawActionHandler | DrawType::DrawCaptureImage);
	}
	else {
		ShPoint3d start = dynamic_cast<ShLine*>((*this->view->preview.Begin()))->GetStart();
		ShObjectSnapState_Perpendicular *state = dynamic_cast<ShObjectSnapState_Perpendicular*>(this->objectSnapState);

		if(state->FindSnapPoint(event,start.x,start.y)==true)
			drawType = (DrawType)(drawType | DrawType::DrawActionHandler | DrawType::DrawCaptureImage);
	
	}

	this->child->MouseMoveEvent(event, point, drawType);
}



ShDrawLineDecorator_SnapMode_Perpendicular* ShDrawLineDecorator_SnapMode_Perpendicular::Clone() {

	return new ShDrawLineDecorator_SnapMode_Perpendicular(*this);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////


ShDrawLineDecorator_Orthogonal::ShDrawLineDecorator_Orthogonal(ShDrawLineAction *drawLineAction, ShGraphicView *view)
	:ShDrawLineDecorator(drawLineAction, view) {

	if (this->GetStatus() == ShDrawLineAction::Status::PickedStart) {

		ShLine *line = dynamic_cast<ShLine*>((*this->view->preview.Begin()));
		this->ApplyLineEndPointToOrthogonal(line);
		this->view->update((DrawType)(DrawCaptureImage | DrawPreviewEntities | DrawActionHandler));
	}
}


ShDrawLineDecorator_Orthogonal::ShDrawLineDecorator_Orthogonal(const ShDrawLineDecorator_Orthogonal& other)
	: ShDrawLineDecorator(other) {

	if (this->GetStatus() == ShDrawLineAction::Status::PickedStart) {

		ShLine *line = dynamic_cast<ShLine*>((*this->view->preview.Begin()));
		this->ApplyLineEndPointToOrthogonal(line);
		this->view->update((DrawType)(DrawCaptureImage | DrawPreviewEntities | DrawActionHandler));
	}
}

ShDrawLineDecorator_Orthogonal::~ShDrawLineDecorator_Orthogonal() {

}

void ShDrawLineDecorator_Orthogonal::MousePressEvent(QMouseEvent *event, ShPoint3d point) {
	
	if (this->child == 0) {
		qDebug("subDrawLineAction is a null pointer.");
		return;
	}

	
	if (this->GetStatus() == ShDrawLineAction::PickedNothing)
		this->child->MousePressEvent(event, point);
	else if (this->GetStatus() == ShDrawLineAction::PickedStart) {

		ShLine *line = dynamic_cast<ShLine*>((*this->view->preview.Begin()));
		this->child->MousePressEvent(event, line->GetEnd());
	}



	if (this->GetStatus() == ShDrawLineAction::Status::PickedStart) {

		ShLine *line = dynamic_cast<ShLine*>((*this->view->preview.Begin()));
		this->ApplyLineEndPointToOrthogonal(line);
	}


}

void ShDrawLineDecorator_Orthogonal::MouseMoveEvent(QMouseEvent *event, ShPoint3d point, DrawType& drawType) {

	if (this->child == 0) {
		qDebug("subDrawLineAction is a null pointer.");
		return;
	}

	this->child->MouseMoveEvent(event, point, drawType);

	if (this->GetStatus() == ShDrawLineAction::Status::PickedStart) {
	
		ShLine *line = dynamic_cast<ShLine*>((*this->view->preview.Begin()));
		this->ApplyLineEndPointToOrthogonal(line);
	}


}

void ShDrawLineDecorator_Orthogonal::Draw(QPainter *painter) {

	this->child->Draw(painter);
}

void ShDrawLineDecorator_Orthogonal::Decorate(ShDrawLineDecorator *drawLineDecorator) {

	if (drawLineDecorator == 0) {
		qDebug("variable is a null pointer.");
		return;
	}

	if (dynamic_cast<ShDrawLineDecorator_Orthogonal*>(drawLineDecorator)) {

		delete drawLineDecorator;

		if (this->GetStatus() == ShDrawLineAction::Status::PickedStart) {
			
			ShLine *line = dynamic_cast<ShLine*>((*this->view->preview.Begin()));
			this->ApplyLineEndPointToMouse(line);
			this->view->update((DrawType)(DrawCaptureImage | DrawPreviewEntities | DrawActionHandler));
		}


		this->drawLineAction->ChangeSubAction(this->child->Clone());

		
		
	}
	else if (dynamic_cast<ShDrawLineDecorator_SnapMode*>(drawLineDecorator)) {
	
		if (dynamic_cast<ShDrawLineDecorator_SnapMode*>(this->child)) {
			
			delete drawLineDecorator;
			this->SetChild(dynamic_cast<ShDrawLineDecorator_SnapMode*>(this->child)->GetChild()->Clone());
		}
		else {

			drawLineDecorator->SetChild(this->child->Clone());
			this->SetChild(drawLineDecorator);
		}
		
	}

}


ShDrawLineDecorator_Orthogonal* ShDrawLineDecorator_Orthogonal::Clone() {

	return new ShDrawLineDecorator_Orthogonal(*this);
}

#include "ShMath.h"
void ShDrawLineDecorator_Orthogonal::GetOrthogonal(double x, double y, double mouseX, double mouseY, double &orthX, double &orthY) {

	double disVertical, disHorizontal;

	disVertical = Math::GetDistance(x, y, x, mouseY);

	disHorizontal = Math::GetDistance(x, y, mouseX, y);

	if (Math::Compare(disVertical, disHorizontal) == 1) {

		orthX = x;
		orthY = mouseY;

	}
	else {

		orthX = mouseX;
		orthY = y;
	}
}

void ShDrawLineDecorator_Orthogonal::ApplyLineEndPointToOrthogonal(ShLine *line) {

	ShLineData data = line->GetData();
	ShPoint3d orth, mouse;
	QPoint pos = this->view->mapFromGlobal(QCursor::pos());

	this->view->ConvertDeviceToEntity(pos.x(),pos.y(), mouse.x, mouse.y);
	this->GetOrthogonal(data.start.x, data.start.y, mouse.x, mouse.y, orth.x, orth.y);

	data.end = orth;
	line->SetData(data);

}

void ShDrawLineDecorator_Orthogonal::ApplyLineEndPointToMouse(ShLine *line) {

	ShLineData data = line->GetData();
	ShPoint3d mouse;

	QPoint pos = this->view->mapFromGlobal(QCursor::pos());
	this->view->ConvertDeviceToEntity(pos.x(), pos.y(), mouse.x, mouse.y);

	data.end = mouse;
	line->SetData(data);
}