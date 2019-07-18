

#include "ShDefaultAction.h"
#include <QMouseEvent>
#include "Base\ShGlobal.h"
#include "Event\ShNotifyEvent.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"
#include "Manager\ShLanguageManager.h"

ShDefaultAction::ShDefaultAction(ShCADWidget *widget)
	:ShActionHandler(widget) {

	this->subDefaultAction = new ShSubDefaultAction_Default(this, this->widget);
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

void ShDefaultAction::keyPressEvent(ShActionData &data) {

	if (data.keyEvent->modifiers() == Qt::Modifier::CTRL && data.keyEvent->key() == Qt::Key::Key_Z) {

		this->changeSubAction(new ShSubDefaultAction_Default(this, this->widget));
		ShGlobal::undo(this->widget);
	}
	else if (data.keyEvent->modifiers() == Qt::Modifier::CTRL && data.keyEvent->key() == Qt::Key::Key_Y) {

		this->changeSubAction(new ShSubDefaultAction_Default(this, this->widget));
		ShGlobal::redo(this->widget);

	}
	else if (data.keyEvent->modifiers() == Qt::Modifier::CTRL && data.keyEvent->key() == Qt::Key::Key_A) {

		

	}
	else if (data.keyEvent->key() == Qt::Key::Key_Delete) {

	}
	else if (data.keyEvent->key() == Qt::Key::Key_Escape) {

		this->changeSubAction(new ShSubDefaultAction_Default(this, this->widget));
		
		ShUpdateTextToCommandListEvent notifyEvent(shGetLanValue_command("Command/<Cancel>"));
		this->widget->notify(&notifyEvent);
	}
	else {

		ShKeyPressedEvent notifyEvent(data.keyEvent);
		this->widget->notify(&notifyEvent);

	}
}

ActionType ShDefaultAction::getType() {

	return ActionType::ActionDefault;
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