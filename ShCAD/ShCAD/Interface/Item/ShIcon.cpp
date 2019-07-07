

#include "ShIcon.h"
#include <qpixmap.h>
#include <qbitmap.h>
ShIcon::ShIcon(const QString &filePath, const QColor &maskFromColor) {

	QPixmap pix(filePath);
	QBitmap mask = pix.createMaskFromColor(maskFromColor, Qt::MaskMode::MaskInColor);
	pix.setMask(mask);

	QIcon::operator=(pix);

}

ShIcon::~ShIcon() {


}

ShIcon& ShIcon::operator=(const ShIcon &icon) {

	QIcon::operator=(icon);

	return *this;
}

