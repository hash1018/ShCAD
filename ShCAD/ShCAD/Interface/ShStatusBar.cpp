

#include "ShStatusBar.h"
#include <qlabel.h>
#include <qpushbutton.h>
ShStatusBar::ShStatusBar(QWidget *parent)
	:QStatusBar(parent) {

	this->coordinates = new QLabel("Coordinates", this);
	this->coordinates->setFixedWidth(200);
	this->addWidget(this->coordinates);

	
	
	this->addWidget(new QPushButton("d", this));
	this->addWidget(new QPushButton("k", this));
}

ShStatusBar::~ShStatusBar() {


}

void ShStatusBar::Update(double x, double y, double z, double zoomRate) {

	QString str = QString::number(x, 'f', 4) + ", " + QString::number(y, 'f', 4) + ", " + QString::number(z,'d',0) + ",  " + QString::number(zoomRate, 'f', 2);
	this->coordinates->setText(str);

}