

#include "ShLayerDialog.h"
#include <qtablewidget.h>
#include "ShLayerTable.h"
#include <qheaderview.h>
ShLayerDialog::ShLayerDialog(ShLayerTable *layerTable, QWidget *parent)
	:QDialog(parent),layerTable(layerTable) {

	this->setFixedSize(500, 400);
	this->setWindowTitle("Layer Setting");
	this->table = new QTableWidget(this);
	this->table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectItems);
	this->table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	this->UpdateLayerList();

	connect(this->table, SIGNAL(cellClicked(int, int)), this, SLOT(CellClicked(int, int)));
}

ShLayerDialog::~ShLayerDialog() {

}


void ShLayerDialog::resizeEvent(QResizeEvent *event) {

	QDialog::resizeEvent(event);

	this->table->setGeometry(20, 100, 460, 200);
}

void ShLayerDialog::UpdateLayerList() {

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


}

void ShLayerDialog::UpdateColumnState(int row) {

	if (row == this->layerTable->GetCurrentLayerIndex()) {
		this->table->setItem(row, 0, new QTableWidgetItem("Current"));
	}
	else {
		this->table->setItem(row, 0, new QTableWidgetItem("Not"));
	}
}

void ShLayerDialog::UpdateColumnName(int row) {

	this->table->setItem(row, 1, new QTableWidgetItem(this->layerTable->GetLayer(row)->GetData().name));
}

void ShLayerDialog::UpdateColumnOnOff(int row) {
	
	bool isTurnOn = this->layerTable->GetLayer(row)->GetData().isTurnOn;
	
	if (isTurnOn == true) {
		this->table->setItem(row, 2, new QTableWidgetItem("On"));
	}
	else{
		this->table->setItem(row, 2, new QTableWidgetItem("Off"));
	}

}

void ShLayerDialog::UpdateColumnColor(int row) {

	ShColor color = this->layerTable->GetLayer(row)->GetData().propertyData.color;

	QString text = QString::number(color.r) + "." + QString::number(color.g) + "." + QString::number(color.b);

	this->table->setItem(row, 3, new QTableWidgetItem(text));

}

#include "Singleton Pattern\ShLineStyleComboList.h"
void ShLayerDialog::UpdateColumnLineStyle(int row) {
	
	ShLineStyleComboList *list = ShLineStyleComboList::GetInstance();

	ShLineStyle lineStyle = this->layerTable->GetLayer(row)->GetData().propertyData.lineStyle;

	this->table->setItem(row, 4, new QTableWidgetItem(list->GetLineStyleText(lineStyle)));

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



#include "Singleton Pattern\ShChangeManager.h"
void ShLayerDialog::Notify(ShNotifyEvent *event) {

	ShChangeManager *manager = ShChangeManager::GetInstance();

	manager->Notify(this, event);

}