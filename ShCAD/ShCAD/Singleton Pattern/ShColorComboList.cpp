

#include "ShColorComboList.h"
#include <qpainter.h>

ShColorComboList ShColorComboList::instance;

ShColorComboList::ShColorComboList() {

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


QPixmap ShColorComboList::GetColorImage(const ShColor& color, int width, int height) {

	QPixmap pix(width, height);
	QPainter painter(&pix);

	painter.fillRect(0, 0, width, height, QColor(color.r, color.g, color.b));

	return pix;

}


QPixmap ShColorComboList::GetColorImage(int width, int height, int index) {

	QPixmap pix(width, height);
	QPainter painter(&pix);

	ShColor color = this->list.at(index);

	painter.fillRect(0, 0, width, height, QColor(color.r, color.g, color.b));

	return pix;
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

