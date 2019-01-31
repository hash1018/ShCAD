

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

	painter.fillRect(0, 0, width, height, QColor(color.GetRed(), color.GetGreen(), color.GetBlue()));

	return pix;

}


QPixmap ShColorComboList::GetColorImage(int width, int height, int index) {

	QPixmap pix(width, height);
	QPainter painter(&pix);

	ShColor color = this->list.at(index);

	painter.fillRect(0, 0, width, height, QColor(color.GetRed(), color.GetGreen(), color.GetBlue()));

	return pix;
}


QString ShColorComboList::GetColorText(int index) {

	ShColor color = this->list.at(index);
	QString text;

	if (color.GetRed() == 255 && color.GetGreen() == 0 && color.GetBlue() == 0)
		text = "Red";
	else if (color.GetRed() == 255 && color.GetGreen() == 255 && color.GetBlue() == 0)
		text = "Yellow";
	else if (color.GetRed() == 0 && color.GetGreen() == 255 && color.GetBlue() == 0)
		text = "Green";
	else if (color.GetRed() == 0 && color.GetGreen() == 255 && color.GetBlue() == 255)
		text = "Sky";
	else if (color.GetRed() == 0 && color.GetGreen() == 0 && color.GetBlue() == 255)
		text = "Blue";
	else if (color.GetRed() == 255 && color.GetGreen() == 255 && color.GetBlue() == 255)
		text = "White";
	else
		text = QString::number(color.GetRed()) + "." + QString::number(color.GetGreen()) +
		"." + QString::number(color.GetBlue());

	return text;
}



int ShColorComboList::Search(const ShColor& color) {

	return this->list.indexOf(color);
}

void ShColorComboList::Add(const ShColor& color) {

	this->list.append(color);
}

