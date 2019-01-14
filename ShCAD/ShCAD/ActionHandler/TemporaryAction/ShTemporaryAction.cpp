

#include "ShTemporaryAction.h"

ShTemporaryAction::ShTemporaryAction(ShGraphicView *graphicView, ShActionHandler *previousAction)
	:ShActionHandler(graphicView), previousAction(previousAction) {

}

ShTemporaryAction::~ShTemporaryAction() {


}

void ShTemporaryAction::ReturnToPrevious() {
	qDebug("ShTemporaryAction->ReturnToPrevious");
	this->graphicView->currentAction = this->previousAction;
	
	delete this;
}