
#include "ShDrawPreviewCommand.h"
#include "Interface\ShGraphicView.h"
#include "ShRubberBand.h"
ShDrawPreviewCommand::ShDrawPreviewCommand(ShGraphicView *view, const ShVector& start, const ShVector& end)
	:view(view), start(start), end(end), isDrawingRubberBand(true) {


}

ShDrawPreviewCommand::ShDrawPreviewCommand(ShGraphicView *view)
	: view(view) {

}

ShDrawPreviewCommand::~ShDrawPreviewCommand() {

}

void ShDrawPreviewCommand::Execute() {

	if (this->isDrawingRubberBand == true) {

		if (this->view->rubberBand == NULL) {
			this->view->rubberBand = new ShRubberBand(this->start, this->end);
		}
		else {
			this->view->rubberBand->SetStartX(this->start.x);
			this->view->rubberBand->SetStartY(this->start.y);
			this->view->rubberBand->SetEndX(this->end.x);
			this->view->rubberBand->SetEndY(this->end.y);
		}
	}
	else {
	
		if (this->view->rubberBand != NULL) {
			delete this->view->rubberBand;
			this->view->rubberBand = NULL;
		}
	}

	this->view->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

}

void ShDrawPreviewCommand::SetDrawingRubberBand(bool enabled) {

	this->isDrawingRubberBand = enabled;
}

void ShDrawPreviewCommand::SetStart(const ShVector& rubberBandStart) {

	this->start = rubberBandStart;
}

void ShDrawPreviewCommand::SetEnd(const ShVector& rubberBandEnd) {

	this->end = rubberBandEnd;
}