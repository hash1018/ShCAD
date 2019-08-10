
#include "ShLineStyleComboBox.h"
#include "Data\ShLineStyleList.h"
#include "Utility\ShLineStyleConverter.h"

ShLineStyleComboBox::ShLineStyleComboBox(QWidget *parent)
	:QComboBox(parent), lineStyleComboSelChangedByUser(true), lineStyleComboIndex(0),
	layerLineStyle(0xFFFF, ShLineStyle::Type::ByLayer), blockLineStyle(0xFFFF, ShLineStyle::Type::ByBlock) {

	this->updateLineStyleCombo();

	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(lineStyleComboIndexChanged(int)));
}

ShLineStyleComboBox::~ShLineStyleComboBox() {


}

void ShLineStyleComboBox::setBlockLineStyle(const ShLineStyle &blockLineStyle) {

	this->blockLineStyle = blockLineStyle;
}

void ShLineStyleComboBox::setLayerLineStyle(const ShLineStyle &layerLineStyle) {

	this->layerLineStyle = layerLineStyle;
}

void ShLineStyleComboBox::updateLineStyleCombo() {

	this->lineStyleComboSelChangedByUser = false;

	this->clear();

	ShLineStyleList *list = ShLineStyleList::getInstance();

	this->addItem("ByBlock " + ShLineStyleConverter::getLineStyleShape(this->blockLineStyle.getPattern()));
	this->addItem("ByLayer " + ShLineStyleConverter::getLineStyleShape(this->layerLineStyle.getPattern()));

	for (int i = 0; i < list->getSize(); i++)
		this->addItem(ShLineStyleConverter::getLineStyleText(list->getLineStyle(i).getPattern()) +
			ShLineStyleConverter::getLineStyleShape(list->getLineStyle(i).getPattern()));

	this->lineStyleComboSelChangedByUser = true;
}

void ShLineStyleComboBox::setLineStyleComboCurrentIndex(int index) {

	this->lineStyleComboSelChangedByUser = false;
	this->setCurrentIndex(index);
	this->lineStyleComboSelChangedByUser = true;
	this->lineStyleComboIndex = index;
}

void ShLineStyleComboBox::lineStyleComboIndexChanged(int index) {

	if (this->lineStyleComboSelChangedByUser == false)
		return;

	this->lineStyleComboIndex = index;

	ShLineStyleList *list = ShLineStyleList::getInstance();

	ShLineStyle lineStyle;

	if (this->lineStyleComboIndex == 0)
		lineStyle = this->blockLineStyle;
	else if (this->lineStyleComboIndex == 1)
		lineStyle = this->layerLineStyle;
	else
		lineStyle = list->getLineStyle(this->lineStyleComboIndex - 2);

	emit lineStyleChanged(lineStyle);
}