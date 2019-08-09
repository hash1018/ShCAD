
#include "ShColorConverter.h"
#include <qpainter.h>
#include "Data\ShColor.h"

ShColorConverter::ShColorConverter() {

}

ShColorConverter::~ShColorConverter() {

}

QPixmap ShColorConverter::convertColorImage(const ShColor &color, int width, int height) {

	QPixmap pix(width, height);
	QPainter painter(&pix);

	painter.fillRect(0, 0, width, height, QColor(color.getRed(), color.getGreen(), color.getBlue()));

	return pix;
}

QString ShColorConverter::convertColorText(const ShColor &color) {

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