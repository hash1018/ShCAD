
#include "ShStatusBar.h"
#include <qlabel.h>
#include "Interface\Item\ShButton.h"
#include "Interface\Item\ShIcon.h"


ShStatusBar::ShStatusBar(QWidget *parent)
	:QStatusBar(parent) {

	this->coordinates = new QLabel("Coordinates", this);
	this->coordinates->setFixedWidth(200);
	this->addWidget(this->coordinates);

	this->orthogonalButton = new ShStateButton(this);
	this->addWidget(this->orthogonalButton);
	this->orthogonalButton->setFixedSize(this->height(), this->height());
	this->orthogonalButton->setIcon(ShIcon(":/Image/Orthogonal.png"));
	this->orthogonalButton->setShortcut(QKeySequence(Qt::Key::Key_F8));

	this->objectSnapButton = new ShStateButton(this);
	this->addWidget(this->objectSnapButton);
	this->objectSnapButton->setFixedSize(this->height(), this->height());
	this->objectSnapButton->setIcon(ShIcon(":/Image/Snap/SnapModeOnOff.png"));
	this->objectSnapButton->setShortcut(QKeySequence(Qt::Key::Key_F3));

}

ShStatusBar::~ShStatusBar() {


}
