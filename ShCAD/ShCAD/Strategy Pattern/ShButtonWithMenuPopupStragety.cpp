
#include "ShButtonWithMenuPopupStrategy.h"
#include "ShDirectoryManager.h"
#include <qpixmap.h>
#include <qbitmap.h>
#include <qaction.h>
ShButtonWithMenuPopupStrategyList::ShButtonWithMenuPopupStrategyList()
	:currentIndex(0) {

}

ShButtonWithMenuPopupStrategyList::~ShButtonWithMenuPopupStrategyList() {

	for (int i = 0; i < this->list.length(); i++)
		delete this->list.at(i);
}

void ShButtonWithMenuPopupStrategyList::Clear() {

	for (int i = 0; i < this->list.length(); i++)
		delete this->list.at(i);

	this->list.clear();

}

void ShButtonWithMenuPopupStrategyList::Add(ShButtonWithMenuPopupStrategy *strategy) {

	this->list.append(strategy);
}


ShCircleButtonStrategyList::ShCircleButtonStrategyList() {

	this->list.append(new ShCircleButtonCenterRadiusStrategy);
	this->list.append(new ShCircleButtonCenterDiameterStrategy);

}

ShCircleButtonStrategyList::~ShCircleButtonStrategyList() {

}

//////////////////////////////////////////////////////////////////////////////////

ShButtonWithMenuPopupStrategy::ShButtonWithMenuPopupStrategy() {

}

ShButtonWithMenuPopupStrategy::~ShButtonWithMenuPopupStrategy() {


}

////////////////////////////////////////////////////////////////////////////////////

ShCircleButtonCenterRadiusStrategy::ShCircleButtonCenterRadiusStrategy() {

}

ShCircleButtonCenterRadiusStrategy::~ShCircleButtonCenterRadiusStrategy() {

}

#include <qmessagebox.h>
void ShCircleButtonCenterRadiusStrategy::Do() {

	QMessageBox box;
	box.setText("Center Radius");
	box.exec();
}

QIcon ShCircleButtonCenterRadiusStrategy::GetIcon() const {

	QString path = ShDirectoryManager::GetImageUiPath();

	QPixmap pix(path + "\\Circle.png");
	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);

	QIcon icon(pix);

	return icon;

}

QAction* ShCircleButtonCenterRadiusStrategy::GetAction() {

	return new QAction("Center-Radius");
}

/////////////////////////////////////////////////////////////////////////////////////

ShCircleButtonCenterDiameterStrategy::ShCircleButtonCenterDiameterStrategy() {

}

ShCircleButtonCenterDiameterStrategy::~ShCircleButtonCenterDiameterStrategy() {

}

void ShCircleButtonCenterDiameterStrategy::Do() {

	QMessageBox box;
	box.setText("Center Diameter");
	box.exec();

}

QIcon ShCircleButtonCenterDiameterStrategy::GetIcon() const {

	QString path = ShDirectoryManager::GetImageUiPath();

	QPixmap pix(path + "\\Line.png");
	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);

	QIcon icon(pix);

	return icon;

}

QAction* ShCircleButtonCenterDiameterStrategy::GetAction() {

	return new QAction("Center-Diameter");
}