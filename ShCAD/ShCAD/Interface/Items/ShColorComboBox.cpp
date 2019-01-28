

#include "ShColorComboBox.h"
#include "Singleton Pattern\ShColorComboList.h"
#include <qpainter.h>

ShColorComboBox::ShColorComboBox(QWidget *parent)
	:QComboBox(parent), colorComboSelChangedByUser(true), colorComboIndex(0),
	layerColor(255, 255, 255, ShColor::Type::ByLayer),
	blockColor(255, 255, 255, ShColor::Type::ByBlock) {


	this->UpdateColorCombo();

	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(ColorComboIndexChanged(int)));
}

ShColorComboBox::~ShColorComboBox() {

}

void ShColorComboBox::Synchronize(int index) {

	this->UpdateColorCombo();
	this->SetColorComboCurrentIndex(index);
}

void ShColorComboBox::UpdateColorCombo() {

	this->colorComboSelChangedByUser = false;

	this->clear();

	ShColorComboList *list = ShColorComboList::GetInstance();

	this->addItem(QIcon(list->GetColorImage(this->blockColor, 10, 10)), "ByBlock");
	this->addItem(QIcon(list->GetColorImage(this->layerColor, 10, 10)), "ByLayer");

	for (int i = 0; i < list->GetSize(); i++) {

		this->addItem(QIcon(list->GetColorImage(10, 10, i)), list->GetColorText(i));
	}


	QPixmap pix(10, 10);
	QPainter painter(&pix);
	QLinearGradient linearGrad(0, 0, 10, 10);
	linearGrad.setColorAt(0, QColor(Qt::white));
	linearGrad.setColorAt(1, QColor(Qt::black));

	painter.fillRect(0, 0, 10, 10, linearGrad);
	
	this->addItem(QIcon(pix), "Custom");


	this->colorComboSelChangedByUser = true;
}

#include <qcolordialog.h>
void ShColorComboBox::OpenColorPickDialog() {

	QColorDialog dialog;

	if (QDialog::Accepted == dialog.exec()) {

		ShColor color = ShColor(dialog.currentColor().red(), dialog.currentColor().green(),
			dialog.currentColor().blue());

		ShColorComboList *list = ShColorComboList::GetInstance();

		int index = list->Search(color);

		if (index != -1) {
			this->SetColorComboCurrentIndex(index + 2); //ByLayer,ByBlock are not in the list.
		}
		else {
			list->Add(color);
			this->UpdateColorCombo();
			this->SetColorComboCurrentIndex(this->count() - 2);
		}

		//Here pass NotifyEvent.
		if (this->colorComboIndex == 0)
			color = this->blockColor;
		else if (this->colorComboIndex == 1)
			color = this->layerColor;
		else
			color=list->GetColor(this->colorComboIndex - 2);
		

		
		emit ColorChanged(color);

	}
	else {
		//Nothing changed.
		this->SetColorComboCurrentIndex(this->colorComboIndex);
	}
}

void ShColorComboBox::SetColorComboCurrentIndex(int index) {

	this->colorComboSelChangedByUser = false;
	this->setCurrentIndex(index);
	this->colorComboSelChangedByUser = true;
	this->colorComboIndex = index;

}


void ShColorComboBox::ColorComboIndexChanged(int index) {

	if (this->colorComboSelChangedByUser == false)
		return;

	if (index == this->count() - 1) {

		//means select custom item list.
		this->OpenColorPickDialog();

	}
	else {
		this->colorComboIndex = index;

		ShColorComboList *list = ShColorComboList::GetInstance();

		//Here pass notifyEvent.
		ShColor color;
		
		if (this->colorComboIndex == 0)
			color = this->blockColor;
		else if (this->colorComboIndex == 1)
			color = this->layerColor;
		else
			color = list->GetColor(this->colorComboIndex - 2);

		
		emit ColorChanged(color);

	}


}

void ShColorComboBox::SetBlockColor(const ShColor& blockColor) {

	this->blockColor = blockColor;
}

void ShColorComboBox::SetLayerColor(const ShColor& layerColor) {

	this->layerColor = layerColor;
}