

#include "ShLayerComboBox.h"
#include "ShLayer.h"
#include "ShLayerTable.h"
#include <qpainter.h>
#include <qvariant.h>
#include <qstylepainter.h>
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

		QRect rect = option.rect.adjusted(0, 0, -170, 0);
		if (data.isTurnOn == true) {
			painter->drawText(rect, "True");
			
		}
		else {
			painter->drawText(rect, "False");
		}

		rect = option.rect.adjusted(40, 0, -100, 0);
		painter->drawText(rect, data.name);

		rect = option.rect.adjusted(110, 0, 0, 0);
		painter->drawText(rect, QString::number(data.propertyData.color.r) + "dd" +
			QString::number(data.propertyData.color.g) + "dd" +
			QString::number(data.propertyData.color.b));

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

#include <qmessagebox.h>
#include <QMouseEvent>
void ShLayerView::mousePressEvent(QMouseEvent *event) {
	
	QModelIndex index = this->currentIndex();
	
	// in case list view is clicked 
	// when it has no (focus? , highligt or something.)
	// I don't know how to describe
	if (index.row() < 0) 
		return;

	QRect rect = this->visualRect(index);
	
	
	
	//change turn on / off
	if (event->x() <= rect.topLeft().x() + 30) {

		int currentLayerIndex = this->comboBox->layerTable->GetCurrentLayerIndex();
		ShLayer *layer = this->comboBox->layerTable->GetLayer(index.row());

		if (layer->GetData().isTurnOn == true)
			layer->GetData().isTurnOn = false;
		else
			layer->GetData().isTurnOn = true;

	
		emit LayerTurnChanged(layer); // when fuction is called, that slots to LayerTrunChanged
		                         // Updates ComboBox Items again, 
		                         // and ListView which is this instance does not disappear 
		                         // after that mousePressEvent is called again with no focus?
		                         // QModelIndex's row is -1
		                         // I still don't understand mechanism.
		




	}
	else {
	
		emit CurrentIndexChanged(index.row());
	}
	






	



}


ShLayerComboBox::ShLayerComboBox(QWidget *parent)
	:QComboBox(parent),layerTable(0) {

	this->setFixedWidth(200);

	
	this->view = new ShLayerView(this);
	this->view->setItemDelegate(new ShLayerDelegate(this));
	this->setView(this->view);
	
	
	connect(this->view, SIGNAL(CurrentIndexChanged(int)), this, SLOT(ComboSelChanged(int)));
	connect(this->view, SIGNAL(LayerTurnChanged(ShLayer*)), this, SLOT(LayerOnOffChanged(ShLayer*)));

	
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


	ShLayerData data = this->layerTable->GetCurrentLayer()->GetData();

	QRect drawRect = rect.adjusted(0, 0, -170, 0);
	if (data.isTurnOn == true) {
		painter.drawText(rect, "True");
	}
	else {
		painter.drawText(rect, "False");
	}

	drawRect = rect.adjusted(40, 0, -100, 0);
	painter.drawText(drawRect, data.name);

	drawRect = rect.adjusted(110, 0, 0, 0);
	painter.drawText(drawRect, QString::number(data.propertyData.color.r) + "dd" +
		QString::number(data.propertyData.color.g) + "dd" +
		QString::number(data.propertyData.color.b));
	
	
}

void ShLayerComboBox::SetLayerTable(ShLayerTable *layerTable) {

	this->layerTable = layerTable;
}

void ShLayerComboBox::Synchronize() {

	this->UpdateLayerCombo();
	this->SetLayerComboCurrentIndex(this->layerTable->GetCurrentLayerIndex());
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

	this->layerTable->SetCurrentLayerIndex(index);
	
	emit CurrentLayerChanged();
	
}

void ShLayerComboBox::LayerOnOffChanged(ShLayer* layer) {
	
	this->UpdateLayerCombo();
	
	emit LayerTurnChanged(layer);
}
