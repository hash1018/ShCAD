
#include "ShActionHandler.h"
#include <qpainter.h>

ShActionHandler::ShActionHandler(ShCADWidget *widget)
	:widget(widget) {

}

ShActionHandler::~ShActionHandler() {

}

void ShActionHandler::mouseLeftPressEvent(ShActionData &data) {

}

void ShActionHandler::mouseMidPressEvent(ShActionData &data) {

}

void ShActionHandler::mouseRightPressEvent(ShActionData &data) {

}

void ShActionHandler::mouseMoveEvent(ShActionData &data) {

}

void ShActionHandler::mouseReleaseEvent(ShActionData &data) {

}


void ShActionHandler::keyPressEvent(ShActionData &data) {

}

void ShActionHandler::draw(QPainter *painter) {

}


QCursor ShActionHandler::getCursorShape() {

	QPixmap pix(48, 48);
	pix.fill(Qt::transparent);
	QPainter painter(&pix);
	painter.setPen(QColor(255, 255, 255));

	painter.drawLine(24, 0, 24, 48);
	painter.drawLine(0, 24, 48, 24);

	painter.drawRect(21, 21, 6, 6);

	return QCursor(pix);
}