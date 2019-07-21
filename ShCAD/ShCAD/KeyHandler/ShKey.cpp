
#include "ShKey.h"
#include <qmessagebox.h>
#include "Interface\ShCADWidget.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "ActionHandler\TemporaryAction\ShTemporaryAction.h"


ShKey::ShKey(KeyType keyType, const Qt::Key &key, const Qt::KeyboardModifiers &modifier)
	:keyType(keyType), key(key), modifier(modifier) {


}

ShKey::~ShKey() {

}

bool ShKey::operator==(const ShKey &other) {

	if (this->key == other.key && this->modifier == other.modifier)
		return true;

	return false;
}

bool ShKey::compare(const Qt::Key &key, const Qt::KeyboardModifiers &modifier) {

	if (this->key == key && this->modifier == modifier)
		return true;
	
	return false;
}

ShKey& ShKey::operator=(const ShKey &other) {

	this->key = other.key;
	this->modifier = other.modifier;

	return *this;
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

bool ShEscKey::operator==(const ShEscKey &other) {

	return ShKey::operator==(other);
}

ShEscKey& ShEscKey::operator=(const ShEscKey &other) {

	ShKey::operator=(other);

	return *this;
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

bool ShEnterKey::operator==(const ShEnterKey &other) {

	return ShKey::operator==(other);
}

ShEnterKey& ShEnterKey::operator=(const ShEnterKey &other) {

	ShKey::operator=(other);

	return *this;
}

void ShEnterKey::pressed(ShCADWidget *widget, ShActionHandler *actionHandler) {

	QMessageBox box;
	box.setText("EnterKey::enter");
	box.exec();
	
}

////////////////////////////////////////////////////////////////////////

ShReturnKey::ShReturnKey()
	:ShKey(KeyType::Return, Qt::Key::Key_Return) {

}

ShReturnKey::~ShReturnKey() {

}

bool ShReturnKey::operator==(const ShReturnKey &other) {

	return ShKey::operator==(other);
}

ShReturnKey& ShReturnKey::operator=(const ShReturnKey &other) {

	ShKey::operator=(other);
	
	return *this;
}

void ShReturnKey::pressed(ShCADWidget *widget, ShActionHandler *actionHandler) {

	QMessageBox box;
	box.setText("ReturnKey::enter");
	box.exec();
}