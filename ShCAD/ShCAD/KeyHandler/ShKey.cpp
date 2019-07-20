
#include "ShKey.h"
#include <qmessagebox.h>

ShKey::ShKey(const Qt::Key &key, const Qt::KeyboardModifiers &modifier)
	:key(key), modifier(modifier) {

	
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

///////////////////////////////////////////////////////////////////

ShEscKey::ShEscKey()
	:ShKey(Qt::Key::Key_Escape) {

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

void ShEscKey::press() {

	QMessageBox box;
	box.setText("EscKey::esc");
	box.exec();

}

////////////////////////////////////////////////////////////////////

ShEnterKey::ShEnterKey()
	:ShKey(Qt::Key::Key_Enter, Qt::KeypadModifier) {

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

void ShEnterKey::press() {

	QMessageBox box;
	box.setText("EnterKey::enter");
	box.exec();
	
}

////////////////////////////////////////////////////////////////////////

ShReturnKey::ShReturnKey()
	:ShKey(Qt::Key::Key_Return) {

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

void ShReturnKey::press() {

	QMessageBox box;
	box.setText("ReturnKey::enter");
	box.exec();
}