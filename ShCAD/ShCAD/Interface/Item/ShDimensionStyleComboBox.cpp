
#include "ShDimensionStyleComboBox.h"
#include "Base\ShDimensionStyleTable.h"
#include "Base\ShDimensionStyle.h"

ShDimensionStyleComboBox::ShDimensionStyleComboBox(QWidget *parent)
	:QComboBox(parent), dimensionStyleComboIndex(0), dimensionStyleComboSelChangedByUser(true), dimensionStyleTable(nullptr) {

	this->updateDimensionStyleCombo();

	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(dimensionStyleComboIndexChanged(int)));

}

ShDimensionStyleComboBox::~ShDimensionStyleComboBox() {

}

void ShDimensionStyleComboBox::updateDimensionStyleCombo() {

	if (this->dimensionStyleTable == nullptr)
		return;

	this->dimensionStyleComboSelChangedByUser = false;

	this->clear();

	for (int i = 0; i < this->dimensionStyleTable->getSize(); i++) {
	
		ShDimensionStyle *dimensionStyle = this->dimensionStyleTable->getDimensionStyle(i);
		this->addItem(dimensionStyle->getName());
	}


	this->dimensionStyleComboSelChangedByUser = true;
}

void ShDimensionStyleComboBox::setDimensionStyleComboCurrentIndex(int index) {

	this->dimensionStyleComboSelChangedByUser = false;
	this->setCurrentIndex(index);
	this->dimensionStyleComboSelChangedByUser = true;
	this->dimensionStyleComboIndex = index;
}

void ShDimensionStyleComboBox::setDimensionStyleComboCurrentIndex(ShDimensionStyle *dimensionStyle) {

	this->dimensionStyleComboSelChangedByUser = false;
	int index = this->dimensionStyleTable->getIndex(dimensionStyle);
	this->setCurrentIndex(index);
	this->dimensionStyleComboSelChangedByUser = true;
	this->dimensionStyleComboIndex = index;
}

void ShDimensionStyleComboBox::dimensionStyleComboIndexChanged(int index) {

	if (this->dimensionStyleComboSelChangedByUser == false)
		return;


}