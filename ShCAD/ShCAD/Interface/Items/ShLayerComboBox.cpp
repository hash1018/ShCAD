

#include "ShLayerComboBox.h"
#include "ShLayer.h"
#include "ShLayerTable.h"
#include <qpainter.h>
#include <qvariant.h>
#include <qstylepainter.h>
#include "ShDirectoryManager.h"
#include <qbitmap.h>
ShLayerDelegate::ShLayerDelegate(QWidget *parent)
	:QStyledItemDelegate(parent) {

}

ShLayerDelegate::~ShLayerDelegate() {

}



void ShLayerDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const{


	if (option.state & QStyle::State_HasFocus) {
		
		painter->fillRect(option.rect, option.palette.highlight());

		QPen oldPen = painter->pen();
		QPen pen(Qt::PenStyle::DotLine);
		pen.setColor(QColor(255, 255, 255));
		painter->setPen(pen);

		QRect rect = option.rect.adjusted(0, 0, -1, -1);
		painter->drawRect(rect);

		painter->setPen(oldPen);
	}


	
	
	if (index.data(Qt::UserRole).canConvert<ShLayerData>()) {
		ShLayerData data = qvariant_cast<ShLayerData> (index.data(Qt::UserRole));

		QRect rect = option.rect.adjusted(0, 0, -183, 0);
		QPixmap pix(17, 17);
		

		if (data.IsTurnOn() == true)
			pix.load(ShDirectoryManager::GetImageUiPath() + "\\LayerTurnOn.png");
		else
			pix.load(ShDirectoryManager::GetImageUiPath() + "\\LayerTurnOff.png");
		

		QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
		pix.setMask(mask);

		painter->drawPixmap(rect, pix);



		//Draw Color 
		rect = option.rect.adjusted(22, 2, -165, -3);

		ShColor color = data.GetPropertyData().GetColor();

		painter->fillRect(rect, QColor(color.GetRed(), color.GetGreen(), color.GetBlue()));
		

		rect = option.rect.adjusted(40, 0, 0, 0);
		painter->drawText(rect, data.GetName());
		

	}
	
	
	
	
}

QSize ShLayerDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const {

	return QSize(200, 17);
}



ShLayerView::ShLayerView(ShLayerComboBox *comboBox, QWidget *parent)
	:comboBox(comboBox), QListView(parent) {


}

ShLayerView::~ShLayerView() {

}


#include <QMouseEvent>
#include <qcolordialog.h>
void ShLayerView::mousePressEvent(QMouseEvent *event) {
	
	QModelIndex index = this->currentIndex();
	
	// in case list view is clicked 
	// when it has no (focus? , highligt or something.)
	// I don't know how to describe
	if (index.row() < 0) 
		return;

	QRect rect = this->visualRect(index);
	
	
	
	//change turn on / off
	if (event->x() <= rect.topLeft().x() + 17) {

		//int currentLayerIndex = this->comboBox->layerTable->GetCurrentLayerIndex();
		ShLayer *layer = this->comboBox->layerTable->GetLayer(index.row());

		//bool prev = layer->GetData()isTurnOn;
		bool prev = layer->IsTurnOn();

		if (layer->IsTurnOn() == true)
			layer->TurnOff();
		else
			layer->TurnOn();

	
		emit LayerTurnChanged(layer, prev); // when fuction is called, that slots to LayerTrunChanged
		                         // Updates ComboBox Items again, 
		                         // and ListView which is this instance does not disappear 
		                         // after that mousePressEvent is called again with no focus?
		                         // QModelIndex's row is -1
		                         // I still don't understand mechanism.

	}
	else if (event->x() > rect.topLeft().x() + 17 && event->x() <= rect.topLeft().x() + 34) {
		QColorDialog dialog;
		

		if (QDialog::Accepted == dialog.exec()) {
		
			QColor color = dialog.currentColor();

			ShColor prev = this->comboBox->layerTable->GetLayer(index.row())->GetPropertyData().GetColor();

			ShPropertyData data = this->comboBox->layerTable->GetLayer(index.row())->GetPropertyData();
			data.SetColor(ShColor(color.red(), color.green(), color.blue(),ShColor::Type::ByLayer));

			this->comboBox->layerTable->GetLayer(index.row())->SetPropertyData(data);

			//this->comboBox->layerTable->GetLayer(index.row())->GetPropertyData().color.r = color.red();
			//this->comboBox->layerTable->GetLayer(index.row())->GetPropertyData().color.g = color.green();
			//this->comboBox->layerTable->GetLayer(index.row())->GetPropertyData().color.b = color.blue();
			
			emit LayerColorChanged(this->comboBox->layerTable->GetLayer(index.row()), prev);

			
		}
	}
	else {
	
		emit CurrentIndexChanged(index.row());
		this->comboBox->hidePopup();
	}
	






	



}


ShLayerComboBox::ShLayerComboBox(QWidget *parent)
	:QComboBox(parent),layerTable(0) {

	this->setFixedWidth(200);

	
	this->view = new ShLayerView(this);
	this->view->setItemDelegate(new ShLayerDelegate(this));
	this->setView(this->view);
	
	
	connect(this->view, SIGNAL(CurrentIndexChanged(int)), this, SLOT(ComboSelChanged(int)));
	connect(this->view, SIGNAL(LayerTurnChanged(ShLayer*, bool)), this, SLOT(LayerOnOffChanged(ShLayer*, bool)));
	connect(this->view, SIGNAL(LayerColorChanged(ShLayer*, const ShColor&)), this, SLOT(LayerColorChanged_(ShLayer*, const ShColor&)));

	
}

ShLayerComboBox::~ShLayerComboBox() {


}


void ShLayerComboBox::paintEvent(QPaintEvent *event) {

	
	QStylePainter painter(this);
	painter.setPen(palette().color(QPalette::Text));

	// draw the combobox frame, focusrect and selected etc.
	QStyleOptionComboBox opt;
	initStyleOption(&opt);
	painter.drawComplexControl(QStyle::CC_ComboBox, opt);

	//here is where the customization start!!!
	QRect rect = opt.rect.adjusted(4, 4, -20, -2); //compensate for frame and arrow 

	if (this->layerTable == 0)
		return;

	if (this->layerComboIndex == -1)
		return;

	//ShLayerData data = this->layerTable->GetCurrentLayer()->Get;
	ShLayer *currentLayer = this->layerTable->GetLayer(this->layerComboIndex);
	
	
	int width = rect.width();

	QRect drawRect = rect.adjusted(0, 0, 16 - width, 0);
	QPixmap pix;


	if (currentLayer->IsTurnOn() == true)
		pix.load(ShDirectoryManager::GetImageUiPath() + "\\LayerTurnOn.png");
	else
		pix.load(ShDirectoryManager::GetImageUiPath() + "\\LayerTurnOff.png");


	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);

	painter.drawPixmap(drawRect, pix);



	//Draw Color 
	drawRect = rect.adjusted(22, 2, 32 - width, -3);

	ShColor color = currentLayer->GetPropertyData().GetColor();

	painter.fillRect(drawRect, QColor(color.GetRed(), color.GetGreen(), color.GetBlue()));
		


	drawRect = rect.adjusted(40, 0, 0, 0);
	painter.drawText(drawRect, currentLayer->GetName());
}

void ShLayerComboBox::SetLayerTable(ShLayerTable *layerTable) {

	this->layerTable = layerTable;
}

void ShLayerComboBox::Synchronize() {

	this->UpdateLayerCombo();
	this->SetLayerComboCurrentIndex(this->layerTable->GetCurrentLayerIndex());
}

void ShLayerComboBox::Synchronize(int index) {

	this->UpdateLayerCombo();
	this->SetLayerComboCurrentIndex(index);

}

void ShLayerComboBox::SetLayerComboCurrentIndex(int index) {

	this->layerComboSelChangedByUser = false;
	this->setCurrentIndex(index);
	this->layerComboSelChangedByUser = true;
	this->layerComboIndex = index;

}


void ShLayerComboBox::UpdateLayerCombo() {

	this->layerComboSelChangedByUser = false;

	this->clear();

	
	for (int i = 0; i < this->layerTable->GetSize(); i++) {
	
		ShLayerData data = this->layerTable->GetLayer(i)->GetData();
		QVariant var;
		var.setValue(data);
		this->addItem("", var);
	}




	this->layerComboSelChangedByUser = true;
}


void ShLayerComboBox::ComboSelChanged(int index) {

	this->SetLayerComboCurrentIndex(index);
	
	emit CurrentIndexChanged(index);

}

void ShLayerComboBox::LayerOnOffChanged(ShLayer* layer,bool previous) {
	
	this->UpdateLayerCombo();
	
	emit LayerTurnChanged(layer, previous);
}

void ShLayerComboBox::LayerColorChanged_(ShLayer *layer, const ShColor& previous) {

	this->UpdateLayerCombo();

	emit LayerColorChanged(layer, previous);
}