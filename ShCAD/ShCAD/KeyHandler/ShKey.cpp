
#include "ShKey.h"
#include <qmessagebox.h>
#include "Interface\ShCADWidget.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "ActionHandler\TemporaryAction\ShTemporaryAction.h"
#include "Base\ShGlobal.h"
#include "Manager\ShCommandLogManager.h"

ShKey::ShKey(KeyType keyType, const Qt::Key &key, const Qt::KeyboardModifiers &modifier)
	:keyType(keyType), key(key), modifier(modifier) {


}

ShKey::~ShKey() {

}



bool ShKey::compare(const Qt::Key &key, const Qt::KeyboardModifiers &modifier) {

	if (this->key == key && this->modifier == modifier)
		return true;
	
	return false;
}


KeyType ShKey::getKeyType() {

	return this->keyType;
}

///////////////////////////////////////////////////////////////////

ShEscKey::ShEscKey(KeyType keyType)
	:ShKey(keyType, Qt::Key::Key_Escape) {

}

ShEscKey::~ShEscKey() {


}


void ShEscKey::pressed(ShCADWidget *widget, ShActionHandler *actionHandler) {


	if (this->keyType == EscCancelCurrent) {
		
		ShChangeDefaultAfterCancelingCurrentStrategy strategy;
		widget->changeAction(strategy);
	}
	else if (this->keyType == EscBackToPrevious) {
		
		if (!dynamic_cast<ShTemporaryAction*>(actionHandler))
			return;

		ShReturnToPreviousAfterCancelingTemporaryStrategy strategy(dynamic_cast<ShTemporaryAction*>(actionHandler));
		widget->changeAction(strategy);
	}

}

////////////////////////////////////////////////////////////////////

ShEnterKey::ShEnterKey()
	:ShKey(KeyType::Enter, Qt::Key::Key_Enter, Qt::KeypadModifier) {

}

ShEnterKey::~ShEnterKey() {

}

void ShEnterKey::pressed(ShCADWidget *widget, ShActionHandler *actionHandler) {
	
	actionHandler->interpret(shCommandLogManager->getEditText());
}

////////////////////////////////////////////////////////////////////////

ShReturnKey::ShReturnKey()
	:ShKey(KeyType::Return, Qt::Key::Key_Return) {

}

ShReturnKey::~ShReturnKey() {

}

void ShReturnKey::pressed(ShCADWidget *widget, ShActionHandler *actionHandler) {

	actionHandler->interpret(shCommandLogManager->getEditText());
}

///////////////////////////////////////////////////////////////////////

ShCtrlZKey::ShCtrlZKey()
	:ShKey(KeyType::Control_Z, Qt::Key::Key_Z, Qt::KeyboardModifier::ControlModifier) {

}

ShCtrlZKey::~ShCtrlZKey() {

}


void ShCtrlZKey::pressed(ShCADWidget *widget, ShActionHandler *actionHandler) {

	ShGlobal::undo(widget);
}

///////////////////////////////////////////////////////////////////////////

ShCtrlYKey::ShCtrlYKey()
	:ShKey(KeyType::Control_Y, Qt::Key::Key_Y, Qt::KeyboardModifier::ControlModifier) {

}

ShCtrlYKey::~ShCtrlYKey() {

}


void ShCtrlYKey::pressed(ShCADWidget *widget, ShActionHandler *actionHandler) {

	ShGlobal::redo(widget);
}


/////////////////////////////////////////////////////////////////////////////

ShCtrlAKey::ShCtrlAKey()
	:ShKey(KeyType::Control_A, Qt::Key::Key_A, Qt::KeyboardModifier::ControlModifier) {

}

ShCtrlAKey::~ShCtrlAKey() {

}

void ShCtrlAKey::pressed(ShCADWidget *widget, ShActionHandler *actionHandler) {

	ShGlobal::selectAll(widget);
}