
#include "ShColorComboBox.h"
#include <qpainter.h>
#include <qcolordialog.h>
#include "Data\ShColorList.h"


ShColorComboBox::ShColorComboBox(QWidget *parent)
	:QComboBox(parent), colorComboSelChangedByUser(true), colorComboIndex(0),
	layerColor(255, 255, 255, ShColor::Type::ByLayer), blockColor(255, 255, 255, ShColor::Type::ByBlock) {

	this->updateColorCombo();

	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(colorComboIndexChanged(int)));

}

ShColorComboBox::~ShColorComboBox() {

}

void ShColorComboBox::openColorPickDialog() {

	QColorDialog dialog;

	if (QDialog::Accepted == dialog.exec()) {

		ShColor color = ShColor(dialog.currentColor().red(), dialog.currentColor().green(), dialog.currentColor().blue());

		ShColorList *list = ShColorList::getInstance();
		int index = list->search(color);

		if (index != -1)
			this->setColorComboCurrentIndex(index + 2);
		else {
			list->add(color);
			this->updateColorCombo();
			this->setColorComboCurrentIndex(this->count() - 2);
		}

		if (this->colorComboIndex == 0)
			color = this->blockColor;
		else if (this->colorComboIndex == 1)
			color = this->layerColor;
		else
			color = list->getColor(this->colorComboIndex - 2);

		emit colorChanged(color);
	}
	else {

		this->setColorComboCurrentIndex(this->colorComboIndex);
	}
}

void ShColorComboBox::setBlockColor(const ShColor &blockColor) {

	this->blockColor = blockColor;
}

void ShColorComboBox::setLayerColor(const ShColor &layerColor) {

	this->layerColor = layerColor;
}

void ShColorComboBox::setColorComboCurrentIndex(int index) {

	this->colorComboSelChangedByUser = false;
	this->setCurrentIndex(index);
	this->colorComboSelChangedByUser = true;
	this->colorComboIndex = index;
}

void ShColorComboBox::updateColorCombo() {

	this->colorComboSelChangedByUser = false;

	this->clear();

	ShColorList *list = ShColorList::getInstance();

	this->addItem(QIcon(list->getColorImage(this->blockColor, 10, 10)), "ByBlock");
	this->addItem(QIcon(list->getColorImage(this->layerColor, 10, 10)), "ByLayer");

	for (int i = 0; i < list->getSize(); i++)
		this->addItem(QIcon(list->getColorImage(10, 10, i)), list->getColorText(i));

	QPixmap pix(10, 10);
	QPainter painter(&pix);
	QLinearGradient linearGrad(0, 0, 10, 10);
	linearGrad.setColorAt(0, QColor(Qt::white));
	linearGrad.setColorAt(1, QColor(Qt::black));

	painter.fillRect(0, 0, 10, 10, linearGrad);

	this->addItem(QIcon(pix), "Custom");


	this->colorComboSelChangedByUser = true;
}


void ShColorComboBox::colorComboIndexChanged(int index) {

	if (this->colorComboSelChangedByUser == false)
		return;

	if (index == this->count() - 1) {

		this->openColorPickDialog();
	}
	else {

		this->colorComboIndex = index;

		ShColorList *list = ShColorList::getInstance();

		ShColor color;

		if (this->colorComboIndex == 0)
			color = this->blockColor;
		else if (this->colorComboIndex == 1)
			color = this->layerColor;
		else
			color = list->getColor(this->colorComboIndex - 2);

		emit colorChanged(color);
	}

}