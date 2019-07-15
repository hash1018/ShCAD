
#include "ShStatusBar.h"
#include <qlabel.h>
#include "Interface\Item\ShButton.h"
#include "Interface\Item\ShIcon.h"
#include "Event\ShNotifyEvent.h"

ShStatusBar::ShStatusBar(QWidget *parent)
	:QStatusBar(parent),zoomRate(1) {

	this->coordiLabel = new QLabel("Coordinates", this);
	this->coordiLabel->setFixedWidth(200);
	this->addWidget(this->coordiLabel);

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


	this->updateCoordiLabel();
}

ShStatusBar::~ShStatusBar() {


}

void ShStatusBar::update(ShNotifyEvent *event) {

	if (dynamic_cast<ShMousePositionChangedEvent*>(event)) {
	
		this->point = dynamic_cast<ShMousePositionChangedEvent*>(event)->getPoint();
		this->updateCoordiLabel();
	}
	else if (dynamic_cast<ShZoomRateChangedEvent*>(event)) {
	
		this->zoomRate = dynamic_cast<ShZoomRateChangedEvent*>(event)->getZoomRate();
		this->updateCoordiLabel();
	}

}

void ShStatusBar::updateCoordiLabel() {

	QString str = QString::number(this->point.x, 'f', 4) + ", " +
		QString::number(this->point.y, 'f', 4) + ", " +
		QString::number(this->point.z, 'f', 4) + ",  " +
		QString::number(this->zoomRate, 'f', 2);

	this->coordiLabel->setText(str);
}