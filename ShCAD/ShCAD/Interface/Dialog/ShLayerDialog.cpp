

#include "ShLayerDialog.h"
#include <qtablewidget.h>
#include "ShLayerTable.h"
#include <qheaderview.h>
#include "ShDirectoryManager.h"
ShLayerDialog::ShLayerDialog(ShLayerTable *layerTable, QWidget *parent)
	:QDialog(parent),layerTable(layerTable),isItemChangedByUser(true) {

	this->setFixedSize(500, 400);
	this->setWindowTitle("Layer Setting");
	this->table = new QTableWidget(this);
	this->table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectItems);
	this->table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	this->table->setIconSize(QSize(20, 20));
	this->UpdateLayerList();

	connect(this->table, SIGNAL(cellClicked(int, int)), this, SLOT(CellClicked(int, int)));
	connect(this->table, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(CellDoubleClicked(int, int)));
	connect(this->table, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(LayerNameChanged(QTableWidgetItem*)));

}

ShLayerDialog::~ShLayerDialog() {

}


void ShLayerDialog::resizeEvent(QResizeEvent *event) {

	QDialog::resizeEvent(event);

	this->table->setGeometry(20, 100, 460, 200);
}

void ShLayerDialog::UpdateLayerList() {

	this->isItemChangedByUser = false;

	this->table->clear();
	this->table->verticalHeader()->hide();

	this->table->setColumnCount(5);
	this->table->setRowCount(this->layerTable->GetSize());

	this->table->setHorizontalHeaderItem(0, new QTableWidgetItem("State"));
	this->table->setHorizontalHeaderItem(1, new QTableWidgetItem("Name"));
	this->table->setHorizontalHeaderItem(2, new QTableWidgetItem("On/Off"));
	this->table->setHorizontalHeaderItem(3, new QTableWidgetItem("Color"));
	this->table->setHorizontalHeaderItem(4, new QTableWidgetItem("LineStyle"));

	for (int i = 0; i < this->layerTable->GetSize(); i++) {
	
		this->UpdateColumnState(i);
		this->UpdateColumnName(i);
		this->UpdateColumnOnOff(i);
		this->UpdateColumnColor(i);
		this->UpdateColumnLineStyle(i);
	}

	this->isItemChangedByUser = true;

}

#include <qlabel.h>
#include <qbitmap.h>
void ShLayerDialog::UpdateColumnState(int row) {
	
	QLabel *label = new QLabel;
	QPixmap pix;

	if (row == this->layerTable->GetCurrentLayerIndex()) {
		
		pix.load(ShDirectoryManager::GetImageUiPath() + "\\CurrentLayer.png");
		QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
		pix.setMask(mask);
		
		label->setPixmap(pix);
		label->setAlignment(Qt::AlignCenter);
	
	}
	
	this->table->setCellWidget(row, 0, label);
}

void ShLayerDialog::UpdateColumnName(int row) {

	QTableWidgetItem *item = new QTableWidgetItem(this->layerTable->GetLayer(row)->GetData().name);
	
	if (row == 0)
		item->setFlags(item->flags()&~Qt::ItemIsEditable);

	item->setTextAlignment(Qt::AlignCenter);
	this->table->setItem(row, 1, item);
}

void ShLayerDialog::UpdateColumnOnOff(int row) {
	
	bool isTurnOn = this->layerTable->GetLayer(row)->GetData().isTurnOn;
	QLabel *label = new QLabel;
	
	
	QPixmap pix(20, 20);
	if (isTurnOn == true)
		pix.load(ShDirectoryManager::GetImageUiPath() + "\\LayerTurnOn.png");
	else
		pix.load(ShDirectoryManager::GetImageUiPath() + "\\LayerTurnOff.png");
		


	
	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);

	label->setPixmap(pix);
	label->setAlignment(Qt::AlignCenter);
	this->table->setCellWidget(row, 2, label);
}

void ShLayerDialog::UpdateColumnColor(int row) {

	ShColor color = this->layerTable->GetLayer(row)->GetData().propertyData.color;
	QString text = QString::number(color.r) + "." + QString::number(color.g) + "." + QString::number(color.b);

	QTableWidgetItem *item = new QTableWidgetItem(text);

	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	item->setTextAlignment(Qt::AlignCenter);
	this->table->setItem(row, 3, item);

}

#include "Singleton Pattern\ShLineStyleComboList.h"
#include <qcombobox.h>
void ShLayerDialog::UpdateColumnLineStyle(int row) {
	
	
	ShLineStyleComboList *list = ShLineStyleComboList::GetInstance();
	/*
	ShLineStyle lineStyle = this->layerTable->GetLayer(row)->GetData().propertyData.lineStyle;

	QTableWidgetItem *item = new QTableWidgetItem(list->GetLineStyleText(lineStyle));

	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	
	this->table->setItem(row, 4, item);
	*/

	QComboBox* combo = new QComboBox;
	ShLineStyle lineStyle;

	for (int i = 0; i < list->GetSize(); i++) {
		lineStyle = list->GetLineStyle(i);
		combo->addItem(list->GetLineStyleText(lineStyle));
	}
	

	int index = list->Search(this->layerTable->GetLayer(row)->GetData().propertyData.lineStyle.pattern);
	combo->setCurrentIndex(index);

	combo->setProperty("row", row);
	combo->setProperty("column", 4);

	connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(LineStyleComboIndexChanged(int)));


	this->table->setCellWidget(row, 4, combo);

}

#include <qcolordialog.h>
#include "ShNotifyEvent.h"
void ShLayerDialog::CellClicked(int row, int column) {

	if (column == 3) {
		QColorDialog dialog;
		
		if (QDialog::Accepted == dialog.exec()) {
			QColor color = dialog.currentColor();
			this->layerTable->GetLayer(row)->GetData().propertyData.color.r = color.red();
			this->layerTable->GetLayer(row)->GetData().propertyData.color.g = color.green();
			this->layerTable->GetLayer(row)->GetData().propertyData.color.b = color.blue();
			
			ShLayerDataChangedEvent event(this->layerTable->GetLayer(row), ShLayerDataChangedEvent::ChangedType::Color);
			this->Notify(&event);

			this->UpdateLayerList();
		}
	}
}

void ShLayerDialog::CellDoubleClicked(int row, int column) {

	if (column == 0) {
	
		this->layerTable->SetCurrentLayerIndex(row);
		ShCurrentLayerChangedEvent event;
		this->Notify(&event);
		this->UpdateLayerList();
	}

	if (column == 2) {

		if (this->layerTable->GetLayer(row)->GetData().isTurnOn == true) {
			this->layerTable->GetLayer(row)->GetData().isTurnOn = false;
		}
		else {
			this->layerTable->GetLayer(row)->GetData().isTurnOn = true;
		}
		ShLayerDataChangedEvent event(this->layerTable->GetLayer(row),
			ShLayerDataChangedEvent::ChangedType::TurnOnOff);
		this->Notify(&event);

		this->UpdateLayerList();
	}
}

#include <qmessagebox.h>
void ShLayerDialog::LayerNameChanged(QTableWidgetItem *item) {

	if (this->isItemChangedByUser == false)
		return;

	if (item->column() != 1)
		return;


	int i = 0;
	bool isSameName = false;
	QString name = item->text();

	while (i < this->layerTable->GetSize() && isSameName != true) {
	
		if (this->layerTable->GetLayer(i)->GetData().name == name) {
		
			if (i != item->row())
				isSameName = true;

		}
	
		i++;
	}

	if (isSameName == true) {

		QMessageBox box;
		box.setText("Name Already Exists.");
		box.exec();
	}
	else {

		this->layerTable->GetLayer(item->row())->GetData().name = name;

		ShLayerDataChangedEvent event(this->layerTable->GetLayer(item->row()),
			ShLayerDataChangedEvent::ChangedType::Name);
		this->Notify(&event);
	}


	this->UpdateLayerList();

}

void ShLayerDialog::LineStyleComboIndexChanged(int index) {

	QComboBox *combo = qobject_cast<QComboBox*>(sender());
	
	if (combo) {
	
		ShLineStyleComboList *list = ShLineStyleComboList::GetInstance();
		ShLineStyle lineStyle = list->GetLineStyle(index);

		int row = combo->property("row").toInt();
		this->layerTable->GetLayer(row)->GetData().propertyData.lineStyle = lineStyle;

		ShLayerDataChangedEvent event(this->layerTable->GetLayer(row), 
			ShLayerDataChangedEvent::ChangedType::LineStyle);

		this->Notify(&event);

	}
}

#include "Singleton Pattern\ShChangeManager.h"
void ShLayerDialog::Notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notify(this, event);

}