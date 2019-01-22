

#include "ShColorComboList.h"
#include <qpainter.h>

ShColorComboList ShColorComboList::instance;

ShColorComboList::ShColorComboList() {

	this->layerColor.type = ShColor::Type::ByLayer;
	this->blockColor.type = ShColor::Type::ByBlock;


	this->list.append(ShColor(255, 0, 0)); //red
	this->list.append(ShColor(255, 255, 0)); //yellow
	this->list.append(ShColor(0, 255, 0));  //green
	this->list.append(ShColor(0, 255, 255)); //sky
	this->list.append(ShColor(0, 0, 255));  //blue
	this->list.append(ShColor(255, 255, 255)); //white

}

ShColorComboList::~ShColorComboList() {

}

ShColorComboList* ShColorComboList::GetInstance() {

	return &(ShColorComboList::instance);
}


QPixmap ShColorComboList::GetLayerColorImage(int width, int height) {

	QPixmap pix(width, height);
	QPainter painter(&pix);

	painter.fillRect(0, 0, width, height, QColor(this->layerColor.r, this->layerColor.g, this->layerColor.b));

	return pix;

}

QPixmap ShColorComboList::GetBlockColorImage(int width, int height) {

	QPixmap pix(width, height);
	QPainter painter(&pix);

	painter.fillRect(0, 0, width, height, QColor(this->blockColor.r, this->blockColor.g, this->blockColor.b));

	return pix;
}

QPixmap ShColorComboList::GetColorImage(int width, int height, int index) {

	QPixmap pix(width, height);
	QPainter painter(&pix);

	ShColor color = this->list.at(index);

	painter.fillRect(0, 0, width, height, QColor(color.r, color.g, color.b));

	return pix;
}

QString ShColorComboList::GetLayerColorText() {

	return "ByLayer";
}

QString ShColorComboList::GetBlockColorText() {

	return "ByBlock";
}

QString ShColorComboList::GetColorText(int index) {

	ShColor color = this->list.at(index);
	QString text;

	if (color.r == 255 && color.g == 0 && color.b == 0)
		text = "Red";
	else if (color.r == 255 && color.g == 255 && color.b == 0)
		text = "Yellow";
	else if (color.r == 0 && color.g == 255 && color.b == 0)
		text = "Green";
	else if (color.r == 0 && color.g == 255 && color.b == 255)
		text = "Sky";
	else if (color.r == 0 && color.g == 0 && color.b == 255)
		text = "Blue";
	else if (color.r == 255 && color.g == 255 && color.b == 255)
		text = "White";
	else
		text = QString::number(color.r) + "." + QString::number(color.g) + "." + QString::number(color.b);

	return text;
}



int ShColorComboList::Search(const ShColor& color) {

	return this->list.indexOf(color);
}

void ShColorComboList::Add(const ShColor& color) {

	this->list.append(color);
}

ShColor ShColorComboList::GetColorUsingComboBoxIndex(int comboBoxIndex) {

	if (comboBoxIndex == 0)
		return this->blockColor;
	else if (comboBoxIndex == 1)
		return this->layerColor;
	


	return this->list.at(comboBoxIndex - 2);
}