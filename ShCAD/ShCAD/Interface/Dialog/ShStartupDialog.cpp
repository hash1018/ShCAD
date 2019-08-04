
#include "ShStartupDialog.h"
#include <qpushbutton.h>
#include <QResizeEvent>

ShStartupDialog::ShStartupDialog(QWidget *parent)
	:QDialog(parent) {

	this->setFixedSize(QSize(600, 400));

	this->okButton = new QPushButton("ok", this);
	this->cancelButton = new QPushButton("cancel", this);

	connect(this->okButton, &QPushButton::pressed, this, &ShStartupDialog::okButtonClicked);
	connect(this->cancelButton, &QPushButton::pressed, this, &ShStartupDialog::cancelButtonClicked);
}

ShStartupDialog::~ShStartupDialog() {


}

void ShStartupDialog::resizeEvent(QResizeEvent *event) {

	QDialog::resizeEvent(event);

	this->okButton->setGeometry(350, 350, 100, 25);
	this->cancelButton->setGeometry(470, 350, 100, 25);
}

void ShStartupDialog::okButtonClicked() {

	this->accept();
	
}

void ShStartupDialog::cancelButtonClicked() {


	this->reject();
	
}

