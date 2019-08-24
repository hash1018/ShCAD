

#include "ShDefaultAction.h"
#include <QMouseEvent>
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"
#include "KeyHandler\ShKeyHandler.h"
#include "KeyHandler\ShCustomKey.h"
#include "Entity\Private\ShSearchEntityStrategy.h"
#include "Entity\Composite\ShSelectedEntities.h"


ShDefaultAction::ShDefaultAction(ShCADWidget *widget)
	:ShActionHandler(widget) {

	this->subDefaultAction = new ShSubDefaultAction_Default(this, this->widget);

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowInput().
		allowKey(KeyType::Control_Z).
		allowKey(KeyType::Control_Y).
		allowCustom(new ShCustomKey<ShDefaultAction>(Qt::Key::Key_Escape, Qt::KeyboardModifier::NoModifier, this, &ShDefaultAction::escPressed)).
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

void ShDefaultAction::escPressed() {

	if (this->widget->getSelectedEntities()->getSize() > 0) {
		this->widget->getSelectedEntities()->unSelectAll();
		this->widget->update(DrawType::DrawAll);
		this->widget->captureImage();
	
	}

	this->changeSubAction(new ShSubDefaultAction_Default(this, this->widget));
	
	shCommandLogManager->appendListEditTextWith((shGetLanValue_command("Command/<Cancel>")));

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

	ShEntity *entity = nullptr;
	ShPoint3d mouse = this->widget->getMousePoint();
	ShSearchEntityUniqueStrategy strategy(&entity, mouse.x, mouse.y, this->widget->getZoomRate());
	this->widget->getEntityTable().search(strategy);
	
	if (entity == nullptr) {
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
	else {
	
		if (data.mouseEvent->modifiers() == Qt::ShiftModifier) {
			
			if (this->widget->getSelectedEntities()->remove(entity) == true) {
			
				this->widget->update(DrawType::DrawAll);
				this->widget->captureImage();
			}
		
		}
		else {
		
			if (this->widget->getSelectedEntities()->add(entity) == true) {
			
				this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
				this->widget->captureImage();
			}
		}
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