
#include "ShStartupDialog.h"
#include <qpushbutton.h>
#include <QResizeEvent>
#include <qcombobox.h>
#include "Manager\ShLanguageManager.h"

ShStartupDialog::ShStartupDialog(QWidget *parent)
	:QDialog(parent) {

	this->setFixedSize(QSize(600, 400));

	this->okButton = new QPushButton("ok", this);
	this->cancelButton = new QPushButton("cancel", this);

	this->languageCombo = new QComboBox(this);
	
	this->languageCombo->addItem(QString::fromLocal8Bit("ÇÑ±¹¾î"));
	this->languageCombo->addItem("English");


	connect(this->okButton, &QPushButton::pressed, this, &ShStartupDialog::okButtonClicked);
	connect(this->cancelButton, &QPushButton::pressed, this, &ShStartupDialog::cancelButtonClicked);
}

ShStartupDialog::~ShStartupDialog() {


}

void ShStartupDialog::resizeEvent(QResizeEvent *event) {

	QDialog::resizeEvent(event);

	this->okButton->setGeometry(350, 350, 100, 25);
	this->cancelButton->setGeometry(470, 350, 100, 25);

	this->languageCombo->setGeometry(20, 100, 150, 25);
}

void ShStartupDialog::okButtonClicked() {

	if (this->languageCombo->currentIndex() == 0) {
		ShLanguageManager::getInstance()->setLanguage(ShLanguageManager::Korean);
	}
	else
		ShLanguageManager::getInstance()->setLanguage(ShLanguageManager::English);


	this->accept();
	
}

void ShStartupDialog::cancelButtonClicked() {


	this->reject();
	
}

