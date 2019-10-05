
#include "ShCommandLogManager.h"
#include "Interface\Dock\ShCommandDock.h"

ShCommandLogManager::ShCommandLogManager() {

}

ShCommandLogManager::~ShCommandLogManager() {

}

void ShCommandLogManager::appendHeadTitle(const QString &headTitle) {

	this->commandDock->setHeadTitle(this->commandDock->getHeadTitle() + headTitle);
	this->commandDock->setEditText("");
}

void ShCommandLogManager::replaceHeadTitle(const QString &headTitle) {

	this->commandDock->setHeadTitle(headTitle);
	this->commandDock->setEditText("");
}

void ShCommandLogManager::appendList(const QString &text) {

	this->commandDock->appendTextToList(text);
}

void ShCommandLogManager::appendListEditTextWith(const QString &text) {

	QString currentText = this->commandDock->getHeadTitle() + this->commandDock->getEditText() + text;
	this->commandDock->appendTextToList(currentText);
	this->commandDock->clearEditText();
}

void ShCommandLogManager::appendListEditTextAndNewLineWith(const QString &text) {

	QString currentText = this->commandDock->getHeadTitle() + this->commandDock->getEditText();
	this->commandDock->appendTextToList(currentText);
	this->commandDock->appendTextToList(this->commandDock->getHeadTitle() + text);
	this->commandDock->clearEditText();
}

QString ShCommandLogManager::getEditText() {

	return this->commandDock->getEditText();
}

QString ShCommandLogManager::getHeadTitle() {

	return this->commandDock->getHeadTitle();
}