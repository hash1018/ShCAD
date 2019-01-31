

#include "ShLayerDialog.h"
#include <qtablewidget.h>
#include "ShLayerTable.h"
#include <qheaderview.h>
#include "ShDirectoryManager.h"
#include <qpushbutton.h>
ShLayerDialog::ShLayerDialog(ShLayerTable *layerTable, QWidget *parent)
	:QDialog(parent),layerTable(layerTable),isItemChangedByUser(true) {

	this->setFixedSize(500, 400);
	this->setWindowTitle("Layer Setting");
	this->table = new QTableWidget(this);
	this->table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	this->table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	this->table->setIconSize(QSize(20, 20));
	this->UpdateLayerList();

	connect(this->table, SIGNAL(cellClicked(int, int)), this, SLOT(CellClicked(int, int)));
	connect(this->table, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(CellDoubleClicked(int, int)));
	connect(this->table, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(LayerNameChanged(QTableWidgetItem*)));


	this->newLayerButton = new QPushButton("New", this);
	this->deleteLayerButton = new QPushButton("Delete", this);

	connect(this->newLayerButton, SIGNAL(released()), this, SLOT(NewLayerButtonClicked()));
	connect(this->deleteLayerButton, SIGNAL(released()), this, SLOT(DeleteLayerButtonClicked()));

}

ShLayerDialog::~ShLayerDialog() {

}


void ShLayerDialog::resizeEvent(QResizeEvent *event) {

	QDialog::resizeEvent(event);

	this->table->setGeometry(20, 100, 460, 200);

	this->newLayerButton->setGeometry(20, 40, 100, 25);
	this->deleteLayerButton->setGeometry(130, 40, 100, 25);
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

	QTableWidgetItem *item = new QTableWidgetItem(this->layerTable->GetLayer(row)->GetData().GetName());
	
	if (row == 0)
		item->setFlags(item->flags()&~Qt::ItemIsEditable);

	item->setTextAlignment(Qt::AlignCenter);
	this->table->setItem(row, 1, item);
}

void ShLayerDialog::UpdateColumnOnOff(int row) {
	
	bool isTurnOn = this->layerTable->GetLayer(row)->GetData().IsTurnOn();
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

	ShColor color = this->layerTable->GetLayer(row)->GetData().GetPropertyData().GetColor();
	QString text = QString::number(color.GetRed()) + "." + QString::number(color.GetGreen()) +
		"." + QString::number(color.GetBlue());

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
	

	int index = list->Search(this->layerTable->GetLayer(row)->GetData().GetPropertyData().GetLineStyle().GetPattern());
	combo->setCurrentIndex(index);

	combo->setProperty("row", row);
	combo->setProperty("column", 4);

	connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(LineStyleComboIndexChanged(int)));


	this->table->setCellWidget(row, 4, combo);

}

#include <qcolordialog.h>
#include "ShNotifyEvent.h"
#include "Memento Pattern\ShMemento.h"
void ShLayerDialog::CellClicked(int row, int column) {

	if (column == 3) {
		QColorDialog dialog;
		
		if (QDialog::Accepted == dialog.exec()) {
			QColor color = dialog.currentColor();

			ShColor prev = this->layerTable->GetLayer(row)->GetData().GetPropertyData().GetColor();

			ShPropertyData data = this->layerTable->GetLayer(row)->GetPropertyData();
			data.SetColor(ShColor(color.red(), color.green(), color.blue(), ShColor::Type::ByLayer));

			this->layerTable->GetLayer(row)->SetPropertyData(data);
			
			ShLayerMemento *memento = this->layerTable->GetLayer(row)->CreateMemento();
			data.SetColor(prev);
			memento->data->SetPropertyData(data);

			ShLayerDataChangedEvent event(this->layerTable->GetLayer(row), memento, ShLayerDataChangedEvent::ChangedType::Color);
			this->Notify(&event);

			this->UpdateLayerList();
		}
	}
}

void ShLayerDialog::CellDoubleClicked(int row, int column) {

	if (column == 0) {
		ShLayer *previousLayer = this->layerTable->GetCurrentLayer();
		this->layerTable->SetCurrentLayerIndex(row);
		ShCurrentLayerChangedEvent event(previousLayer, this->layerTable->GetCurrentLayer());
		this->Notify(&event);
		this->UpdateLayerList();
	}

	if (column == 2) {
		
		bool prev = this->layerTable->GetLayer(row)->IsTurnOn();

		if (this->layerTable->GetLayer(row)->IsTurnOn() == true) {
			this->layerTable->GetLayer(row)->TurnOff();
		}
		else {
			this->layerTable->GetLayer(row)->TurnOn();
		}

		ShLayerMemento *memento = this->layerTable->GetLayer(row)->CreateMemento();
		memento->data->SetTurn(prev);

		ShLayerDataChangedEvent event(this->layerTable->GetLayer(row), memento,
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
	
		if (this->layerTable->GetLayer(i)->GetName() == name) {
		
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

		QString prev = this->layerTable->GetLayer(item->row())->GetName();

		this->layerTable->GetLayer(item->row())->SetName(name);

		ShLayerMemento *memento = this->layerTable->GetLayer(item->row())->CreateMemento();
		memento->data->SetName(prev);

		ShLayerDataChangedEvent event(this->layerTable->GetLayer(item->row()), memento,
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

		ShLineStyle prev = this->layerTable->GetLayer(row)->GetPropertyData().GetLineStyle();
		ShPropertyData data = this->layerTable->GetLayer(row)->GetPropertyData();
		//data.lineStyle.pattern = lineStyle.pattern
		data.SetLineStyle(ShLineStyle(lineStyle.GetPattern(), ShLineStyle::Type::ByLayer));

		this->layerTable->GetLayer(row)->SetPropertyData(data);


		ShLayerMemento *memento = this->layerTable->GetLayer(row)->CreateMemento();
		data.SetLineStyle(prev);
		memento->data->SetPropertyData(data);

		ShLayerDataChangedEvent event(this->layerTable->GetLayer(row), memento,
			ShLayerDataChangedEvent::ChangedType::LineStyle);

		this->Notify(&event);

	}
}

#include "Singleton Pattern\ShChangeManager.h"
void ShLayerDialog::Notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notify(this, event);

}


void ShLayerDialog::NewLayerButtonClicked() {

	ShLayerData data = this->layerTable->GetLayer(this->layerTable->GetSize() - 1)->GetData();

	ShLayer *layer = new ShLayer(data);

	this->layerTable->Add(layer);

	this->UpdateLayerList();

	ShLayerCreatedEvent event(layer);
	this->Notify(&event);

}

void ShLayerDialog::DeleteLayerButtonClicked() {

	int index = this->table->currentRow();

	if (index == 0) {
		QMessageBox box;
		box.setText("This layer cannot be deleted.");
		box.exec();
		return;
	}

	if (index == this->layerTable->GetCurrentLayerIndex()) {
		QMessageBox box;
		box.setText("Current Layer cannot be deleted.");
		box.exec();
		return;
	}

	if (this->layerTable->GetLayer(index)->GetSize() > 0) {
		QMessageBox box;
		box.setText("This layer still has entities on it.");
		box.exec();
		return;
	}


	ShLayer *layer = this->layerTable->GetLayer(index);
	this->layerTable->Remove(layer);

	this->UpdateLayerList();

	ShLayerDeletedEvent event(layer);
	this->Notify(&event);
	
}