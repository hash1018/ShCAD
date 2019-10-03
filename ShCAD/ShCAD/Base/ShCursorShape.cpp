
#include "ShCursorShape.h"
#include <qpixmap.h>
#include <qpainter.h>

ShCursorShape ShCursorShape::instance;

ShCursorShape::ShCursorShape() {

}

ShCursorShape::~ShCursorShape() {

}

ShCursorShape* ShCursorShape::getInstance() {

	return &(ShCursorShape::instance);
}

QCursor ShCursorShape::getCursor(CursorType type) {

	QCursor cursor;

	if (type == CursorType::Default) {

		QPixmap pix(48, 48);
		pix.fill(Qt::transparent);
		QPainter painter(&pix);
		painter.setPen(QColor(255, 255, 255));

		painter.drawLine(24, 0, 24, 48);
		painter.drawLine(0, 24, 48, 24);

		painter.drawRect(21, 21, 6, 6);

		cursor = QCursor(pix);
	}
	else if (type == CursorType::Drawing) {
	
		QPixmap pix(48, 48);
		pix.fill(Qt::transparent);
		QPainter painter(&pix);
		painter.setPen(QColor(255, 255, 255));

		painter.drawLine(24, 0, 24, 48);
		painter.drawLine(0, 24, 48, 24);

		cursor = QCursor(pix);
	}
	else if (type == CursorType::Selecting) {
	
		QPixmap pix(32, 32);
		pix.fill(Qt::transparent); // Otherwise you get a black background :(
		QPainter painter(&pix);
		painter.setPen(QColor(255, 255, 255));
		painter.drawRect(13, 13, 6, 6);

		cursor = QCursor(pix);
	}
	else if (type == CursorType::Nothing) {
	
		QPixmap pix(1, 1);
		pix.fill(Qt::transparent);
		QPainter painter(&pix);
		painter.setPen(QColor(255, 255, 255));
		painter.drawRect(0, 0, 1, 1);

		cursor = QCursor(pix);
	}

	return cursor;
}