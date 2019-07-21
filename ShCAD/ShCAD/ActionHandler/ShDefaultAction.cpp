

#include "ShDefaultAction.h"
#include <QMouseEvent>
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"
#include "Manager\ShLanguageManager.h"
#include "KeyHandler\ShKeyHandler.h"
#include "KeyHandler\ShCustomKey.h"

ShDefaultAction::ShDefaultAction(ShCADWidget *widget)
	:ShActionHandler(widget) {

	this->subDefaultAction = new ShSubDefaultAction_Default(this, this->widget);

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowInput().
		allowKey(KeyType::EscCancelCurrent).
		allowKey(KeyType::Control_Z).
		allowKey(KeyType::Control_Y).
		build();
}

ShDefaultAction::~ShDefaultAction() {

	if (this->subDefaultAction != nullptr)
		delete this->subDefaultAction;
}

void ShDefaultAction::mouseLeftPressEvent(ShActionData &data) {

	this->subDefaultAction->mouseLeftPressEvent(data);
}

void ShDefaultAction::mouseMoveEvent(ShActionData &data) {

	this->subDefaultAction->mouseMoveEvent(data);
}


ActionType ShDefaultAction::getType() {

	return ActionType::ActionDefault;
}

QString ShDefaultAction::getHeadTitle() {

	return shGetLanValue_command("Command/Command");
}

void ShDefaultAction::changeSubAction(ShSubDefaultAction *subDefaultAction) {

	if (this->subDefaultAction != nullptr)
		delete this->subDefaultAction;

	this->subDefaultAction = subDefaultAction;
}

//////////////////////////////////////////////////////////////////////////////////

ShSubDefaultAction::ShSubDefaultAction(ShDefaultAction *defaultAction, ShCADWidget *widget)
	:defaultAction(defaultAction), widget(widget) {

}

ShSubDefaultAction::~ShSubDefaultAction() {

}


////////////////////////////////////////////////////////////////////////////////////



ShSubDefaultAction_Default::ShSubDefaultAction_Default(ShDefaultAction *defaultAction, ShCADWidget *widget)
	:ShSubDefaultAction(defaultAction, widget) {

}

ShSubDefaultAction_Default::~ShSubDefaultAction_Default() {

}

void ShSubDefaultAction_Default::mouseLeftPressEvent(ShActionData &data) {

	if (data.mouseEvent->modifiers() == Qt::ShiftModifier) {
	
		ShChangeTemporaryStrategy strategy(new ShDragSelectAction(this->widget, data.point.x, data.point.y,
			ShDragSelectAction::Mode::UnSelectMode), this->defaultAction);
		this->widget->changeAction(strategy);
	}
		
	else {
		ShChangeTemporaryStrategy strategy(new ShDragSelectAction(this->widget, data.point.x, data.point.y), this->defaultAction);
		this->widget->changeAction(strategy);
	}
		
}

void ShSubDefaultAction_Default::mouseMoveEvent(ShActionData &data) {

}



ShSubDefaultAction_MouseIsInShapeVertex::ShSubDefaultAction_MouseIsInShapeVertex(ShDefaultAction *defaultAction, ShCADWidget *widget)
	:ShSubDefaultAction(defaultAction, widget) {

}

ShSubDefaultAction_MouseIsInShapeVertex::~ShSubDefaultAction_MouseIsInShapeVertex() {

}

void ShSubDefaultAction_MouseIsInShapeVertex::mouseLeftPressEvent(ShActionData &data) {

}

void ShSubDefaultAction_MouseIsInShapeVertex::mouseMoveEvent(ShActionData &data) {

}