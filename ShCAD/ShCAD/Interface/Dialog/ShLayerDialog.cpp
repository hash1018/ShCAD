
#include "ShLayerDialog.h"
#include <qtablewidget.h>
#include <qheaderview.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qbitmap.h>
#include <qcombobox.h>
#include <qmessagebox.h>
#include <qcolordialog.h>
#include "Base\ShLayerTable.h"
#include "Base\ShLayer.h"
#include "Data\ShLineStyleList.h"
#include "Utility\ShLineStyleConverter.h"
#include "Chain of Responsibility\ShRequest.h"
#include "Event\ShNotifyEvent.h"
#include "Manager\ShLanguageManager.h"

ShLayerDialog::ShLayerDialog(const ShLayerTable *layerTable, ShChain *chain, QWidget *parent)
	:QDialog(parent), ShChain(chain), layerTable(layerTable), isItemChangedByUser(true) {

	this->setFixedSize(800, 400);
	this->setWindowTitle(shGetLanValue_ui("Layer/Layer Setting"));
	
	this->table = new QTableWidget(this);
	this->table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	this->table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	this->table->setIconSize(QSize(20, 20));

	this->createLayerButton = new QPushButton(shGetLanValue_ui("Layer/Create"), this);
	this->deleteLayerButton = new QPushButton(shGetLanValue_ui("Layer/Delete"), this);

	this->updateLayerTable();

	connect(this->table, &QTableWidget::cellClicked, this, &ShLayerDialog::cellClicked);
	connect(this->table, &QTableWidget::cellDoubleClicked, this, &ShLayerDialog::cellDoubleClicked);
	connect(this->table, &QTableWidget::itemChanged, this, &ShLayerDialog::layerNameChanged);
	connect(this->createLayerButton, &QPushButton::released, this, &ShLayerDialog::createLayerButtonClicked);
	connect(this->deleteLayerButton, &QPushButton::released, this, &ShLayerDialog::deleteLayerButtonClicked);

}

ShLayerDialog::~ShLayerDialog() {

}

void ShLayerDialog::resizeEvent(QResizeEvent *event) {

	QDialog::resizeEvent(event);

	this->table->setGeometry(20, 100, 760, 200);

	this->createLayerButton->setGeometry(20, 40, 100, 25);
	this->deleteLayerButton->setGeometry(130, 40, 100, 25);
}

void ShLayerDialog::updateLayerTable() {

	this->isItemChangedByUser = false;

	this->table->clear();
	this->table->verticalHeader()->hide();

	this->table->setColumnCount(5);
	this->table->setRowCount(this->layerTable->getSize());

	this->table->setHorizontalHeaderItem(0, new QTableWidgetItem(shGetLanValue_ui("Layer/State")));
	this->table->setHorizontalHeaderItem(1, new QTableWidgetItem(shGetLanValue_ui("Layer/Name")));
	this->table->setHorizontalHeaderItem(2, new QTableWidgetItem(shGetLanValue_ui("Layer/On/Off")));
	this->table->setHorizontalHeaderItem(3, new QTableWidgetItem(shGetLanValue_ui("Layer/Color")));
	this->table->setHorizontalHeaderItem(4, new QTableWidgetItem(shGetLanValue_ui("Layer/LineStyle")));
	

	for (int i = 0; i < this->layerTable->getSize(); i++) {

		this->updateStateColumn(i);
		this->updateNameColumn(i);
		this->updateTurnColumn(i);
		this->updateColorColumn(i);
		this->updateLineStyleColumn(i);
	}

	this->isItemChangedByUser = true;
}

void ShLayerDialog::updateStateColumn(int row) {

	QLabel *label = new QLabel;
	QPixmap pix;

	if (row == this->layerTable->getCurrentLayerIndex()) {

		pix.load(":Image/CurrentLayer.png");
		QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
		pix.setMask(mask);

		label->setPixmap(pix);
		label->setAlignment(Qt::AlignCenter);

	}

	this->table->setCellWidget(row, 0, label);
}

void ShLayerDialog::updateNameColumn(int row) {

	QTableWidgetItem *item = new QTableWidgetItem(this->layerTable->getLayer(row)->getName());

	if (row == 0)
		item->setFlags(item->flags()&~Qt::ItemIsEditable);

	item->setTextAlignment(Qt::AlignCenter);
	this->table->setItem(row, 1, item);
}

void ShLayerDialog::updateTurnColumn(int row) {

	bool isTurnOn = this->layerTable->getLayer(row)->isTurnOn();
	QLabel *label = new QLabel;


	QPixmap pix(20, 20);
	if (isTurnOn == true)
		pix.load(":Image/LayerTurnOn.png");
	else
		pix.load(":Image/LayerTurnOff.png");

	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);

	label->setPixmap(pix);
	label->setAlignment(Qt::AlignCenter);
	this->table->setCellWidget(row, 2, label);
}

void ShLayerDialog::updateColorColumn(int row) {

	ShColor color = this->layerTable->getLayer(row)->getPropertyData().getColor();
	QString text = QString::number(color.getRed()) + "." + QString::number(color.getGreen()) +
		"." + QString::number(color.getBlue());

	QTableWidgetItem *item = new QTableWidgetItem(text);

	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	item->setTextAlignment(Qt::AlignCenter);
	this->table->setItem(row, 3, item);
}

void ShLayerDialog::updateLineStyleColumn(int row) {

	ShLineStyleList *list = ShLineStyleList::getInstance();

	QComboBox* combo = new QComboBox;
	ShLineStyle lineStyle;

	for (int i = 0; i < list->getSize(); i++) {
		lineStyle = list->getLineStyle(i);
		combo->addItem(ShLineStyleConverter::getLineStyleShape(lineStyle.getPattern()));
	}


	int index = list->search(this->layerTable->getLayer(row)->getPropertyData().getLineStyle().getPattern());
	combo->setCurrentIndex(index);

	combo->setProperty("row", row);
	combo->setProperty("column", 4);

	connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(lineStyleComboIndexChanged(int)));

	this->table->setCellWidget(row, 4, combo);
	this->table->setColumnWidth(4, 200);
}

void ShLayerDialog::cellClicked(int row, int column) {

	if (column == 3) {

		QColorDialog dialog;

		if (dialog.exec() == QDialog::Accepted) {
		
			QColor color = dialog.currentColor();
			ShLayerDataChangedEvent event(this->layerTable->getLayer(row), ShColor(color.red(), color.green(), color.blue(), ShColor::Type::ByLayer));
			ShRequestSendNotifyEvent request(&event);
			this->request(&request);
			this->updateLayerTable();
		}
	}
}

void ShLayerDialog::cellDoubleClicked(int row, int column) {

	if (column == 0) {
	
		ShCurrentLayerChangedEvent event(this->layerTable->getLayer(row));
		ShRequestSendNotifyEvent request(&event);
		this->request(&request);
		this->updateLayerTable();
	}
}

void ShLayerDialog::layerNameChanged(QTableWidgetItem *item) {

	if (this->isItemChangedByUser == false)
		return;

	if (item->column() != 1)
		return;

	int i = 0;
	bool isSameName = false;
	QString name = item->text();

	while (i < this->layerTable->getSize() && isSameName != true) {
	
		if (this->layerTable->getLayer(i)->getName() == name)
			if (i != item->row())
				isSameName = true;

		i++;
	}

	if (isSameName == true) {

		QMessageBox box;
		box.setText(shGetLanValue_command("Command/Name Already Exists"));
		box.exec();

		this->updateLayerTable();
	}
	else {
	
		ShLayerDataChangedEvent event(this->layerTable->getLayer(item->row()), name);
		ShRequestSendNotifyEvent request(&event);
		this->request(&request);
		this->updateLayerTable();
	}
	
}

void ShLayerDialog::lineStyleComboIndexChanged(int index) {
	
	QComboBox *combo = qobject_cast<QComboBox*>(sender());

	if (combo) {

		ShLineStyleList *list = ShLineStyleList::getInstance();
		ShLineStyle lineStyle = list->getLineStyle(index);
		lineStyle.setType(ShLineStyle::ByLayer);

		int row = combo->property("row").toInt();
		
		ShLayerDataChangedEvent event(this->layerTable->getLayer(row), lineStyle);
		ShRequestSendNotifyEvent request(&event);
		this->request(&request);
		this->updateLayerTable();
	}
}

void ShLayerDialog::createLayerButtonClicked() {

}

void ShLayerDialog::deleteLayerButtonClicked() {

}