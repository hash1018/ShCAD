

#include "ShLineStyleComboBox.h"
#include "Singleton Pattern\ShLineStyleComboList.h"
ShLineStyleComboBox::ShLineStyleComboBox(QWidget *parent)
	:QComboBox(parent), comboSelChangedByUser(true), comboIndex(0),
	layerLineStyle(0xFFFF, ShLineStyle::Type::ByLayer),
	blockLineStyle(0xFFFF, ShLineStyle::Type::ByBlock) {

	this->UpdateLineStyleCombo();

	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(LineStyleComboIndexChanged(int)));
}

ShLineStyleComboBox::~ShLineStyleComboBox() {

}

void ShLineStyleComboBox::Synchronize(int index) {

	this->UpdateLineStyleCombo();
	this->SetComboCurrentIndex(index);
}

void ShLineStyleComboBox::SetBlockLineStyle(const ShLineStyle& blockLineStyle) {

	this->blockLineStyle = blockLineStyle;
}

void ShLineStyleComboBox::SetLayerLineStyle(const ShLineStyle& layerLineStyle) {

	this->layerLineStyle = layerLineStyle;
}

void ShLineStyleComboBox::UpdateLineStyleCombo() {

	this->comboSelChangedByUser = false;

	this->clear();

	ShLineStyleComboList *list = ShLineStyleComboList::GetInstance();

	this->addItem("ByBlock " + list->GetLineStyleText(this->blockLineStyle));
	this->addItem("ByLayer " + list->GetLineStyleText(this->layerLineStyle));

	for (int i = 0; i < list->GetSize(); i++)
		this->addItem(list->GetLineStyleText(i));


	this->comboSelChangedByUser = true;
}

void ShLineStyleComboBox::SetComboCurrentIndex(int index) {

	this->comboSelChangedByUser = false;
	this->setCurrentIndex(index);
	this->comboSelChangedByUser = true;
	this->comboIndex = index;
}

void ShLineStyleComboBox::LineStyleComboIndexChanged(int index) {

	if (this->comboSelChangedByUser == false)
		return;

	this->comboIndex = index;

	ShLineStyleComboList *list = ShLineStyleComboList::GetInstance();

	ShLineStyle lineStyle;

	if (this->comboIndex == 0)
		lineStyle = this->blockLineStyle;
	else if (this->comboIndex == 1)
		lineStyle = this->layerLineStyle;
	else
		lineStyle = list->GetLineStyle(this->comboIndex - 2);


	emit LineStyleChanged(lineStyle);

}