
#include "ShColorList.h"
#include <qpainter.h>

ShColorList ShColorList::instance;

ShColorList::ShColorList() {

	this->list.append(ShColor(255, 0, 0)); //red
	this->list.append(ShColor(255, 255, 0)); //yellow
	this->list.append(ShColor(0, 255, 0));  //green
	this->list.append(ShColor(0, 255, 255)); //sky
	this->list.append(ShColor(0, 0, 255));  //blue
	this->list.append(ShColor(255, 255, 255)); //white
}

ShColorList::~ShColorList() {

}

ShColorList* ShColorList::getInstance() {

	return &(ShColorList::instance);
}

QPixmap ShColorList::getColorImage(const ShColor &color, int width, int height) {

	QPixmap pix(width, height);
	QPainter painter(&pix);

	painter.fillRect(0, 0, width, height, QColor(color.getRed(), color.getGreen(), color.getBlue()));

	return pix;
}

QPixmap ShColorList::getColorImage(int width, int height, int index) {

	QPixmap pix(width, height);
	QPainter painter(&pix);

	ShColor color = this->list.at(index);

	painter.fillRect(0, 0, width, height, QColor(color.getRed(), color.getGreen(), color.getBlue()));

	return pix;
}

QString ShColorList::getColorText(int index) {

	ShColor color = this->list.at(index);
	QString text;

	if (color.getRed() == 255 && color.getGreen() == 0 && color.getBlue() == 0)
		text = "Red";
	else if (color.getRed() == 255 && color.getGreen() == 255 && color.getBlue() == 0)
		text = "Yellow";
	else if (color.getRed() == 0 && color.getGreen() == 255 && color.getBlue() == 0)
		text = "Green";
	else if (color.getRed() == 0 && color.getGreen() == 255 && color.getBlue() == 255)
		text = "Sky";
	else if (color.getRed() == 0 && color.getGreen() == 0 && color.getBlue() == 255)
		text = "Blue";
	else if (color.getRed() == 255 && color.getGreen() == 255 && color.getBlue() == 255)
		text = "White";
	else
		text = QString::number(color.getRed()) + "." + QString::number(color.getGreen()) +
		"." + QString::number(color.getBlue());

	return text;
}

int ShColorList::search(const ShColor &color) {

	return this->list.indexOf(color);
}

void ShColorList::add(const ShColor &color) {

	this->list.append(color);
}