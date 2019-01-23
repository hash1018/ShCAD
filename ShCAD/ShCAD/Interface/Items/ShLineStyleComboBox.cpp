

#include "ShLineStyleComboBox.h"
#include "Singleton Pattern\ShLineStyleComboList.h"
ShLineStyleComboBox::ShLineStyleComboBox(QWidget *parent)
	:QComboBox(parent) {

	this->UpdateLineStyleCombo();

	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(LineStyleComboIndexChanged(int)));
}

ShLineStyleComboBox::~ShLineStyleComboBox() {

}


void ShLineStyleComboBox::UpdateLineStyleCombo() {

	this->clear();

	ShLineStyleComboList *list = ShLineStyleComboList::GetInstance();

	this->addItem(list->GetBlockLineStyleText());
	this->addItem(list->GetLayerLineStyleText());

	for (int i = 0; i < list->GetSize(); i++)
		this->addItem(list->GetLineStyleText(i));


}

void ShLineStyleComboBox::LineStyleComboIndexChanged(int index) {

	ShLineStyleComboList *list = ShLineStyleComboList::GetInstance();

	emit LineStyleChanged(list->GetColorUsingComboBoxIndex(index));

}