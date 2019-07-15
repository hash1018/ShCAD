

#include "ShDefaultAction.h"
#include <QMouseEvent>
#include "TemporaryAction\ShDragSelectAction.h"
#include "Event\ShNotifyEvent.h"
#include "UnRedo\ShTransaction.h"

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

		if (!this->widget->getUndoStack()->isEmpty()) {
		
			ShTransaction *transaction = this->widget->getUndoStack()->pop();
			transaction->undo();

			this->widget->getRedoStack()->push(transaction);
		}

	}
	else if (data.keyEvent->modifiers() == Qt::Modifier::CTRL && data.keyEvent->key() == Qt::Key::Key_Y) {

		if (!this->widget->getRedoStack()->isEmpty()) {

			ShTransaction *transaction = this->widget->getRedoStack()->pop();
			transaction->redo();

			this->widget->getUndoStack()->push(transaction);
		}

	}
	else if (data.keyEvent->modifiers() == Qt::Modifier::CTRL && data.keyEvent->key() == Qt::Key::Key_A) {

		

	}
	else if (data.keyEvent->key() == Qt::Key::Key_Delete) {

	}
	else if (data.keyEvent->key() == Qt::Key::Key_Escape) {

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

	if (data.mouseEvent->modifiers() == Qt::ShiftModifier)
		this->widget->setTemporaryAction(new ShDragSelectAction(this->widget, this->defaultAction, data.point.x, data.point.y,
			ShDragSelectAction::Mode::UnSelectMode));
	else
		this->widget->setTemporaryAction(new ShDragSelectAction(this->widget, this->defaultAction, data.point.x, data.point.y));
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