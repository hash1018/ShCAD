

#include "ShAbstractToolBar.h"
#include <qbitmap.h>
ShAbstractToolBar::ShAbstractToolBar(const QString& title, QWidget *parent)
	:QToolBar(title, parent),menuActionChecked(false) {

	this->menuAction = new QAction(title);
	this->menuAction->setCheckable(true);

	connect(this->menuAction, &QAction::triggered, this, &ShAbstractToolBar::MenuActionClicked);
}

ShAbstractToolBar::~ShAbstractToolBar() {

	if (this->menuAction != 0)
		delete this->menuAction;

}

void ShAbstractToolBar::GetIcon(const QString& filePath, QIcon& icon) {

	QPixmap pix(filePath);
	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);

	icon = QIcon(pix);
}

void ShAbstractToolBar::MenuActionClicked() {

	if (this->menuActionChecked == false) {
	
		this->menuActionChecked = true;
		this->show();
		this->menuAction->setChecked(true);
	}
	else {
	
		this->menuActionChecked = false;
		this->hide();
		this->menuAction->setChecked(false);
	}
}

void ShAbstractToolBar::Activate() {

	if (this->menuActionChecked == true)
		this->show();
}

void ShAbstractToolBar::DeActivate() {

	if (this->menuActionChecked == true)
		this->hide();
}