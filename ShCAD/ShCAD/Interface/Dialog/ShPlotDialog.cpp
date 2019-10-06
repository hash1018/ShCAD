
#include "ShPlotDialog.h"
#include <qprinterinfo.h>
#include <qprinter.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qspinbox.h>
#include <qpagesetupdialog.h>
#include "Manager\ShPlotManager.h"
#include <qpainter.h>
#include "Interface\Item\ShIcon.h"
#include "Interface\ShCADWidget.h"
#include "Manager\ShCADWidgetManager.h"
#include "ShPlotPreviewDialog.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "ActionHandler\ShSelectPlotAreaAction.h"

ShPlotDialog::ShPlotDialog(QWidget *parent)
	:QDialog(parent), windowPrevX(0), windowPrevY(0), windowCurrentX(0), windowCurrentY(0) {

	this->setMinimumSize(450, 400);
	this->setMaximumSize(450, 400);


	this->createItems();
	this->connectSignals();
	this->updatePrinterInfo();

}

ShPlotDialog::~ShPlotDialog() {


}

void ShPlotDialog::destroy() {

	delete this;
}

void ShPlotDialog::createItems() {

	this->printerGroupBox = new QGroupBox("Printer", this);
	this->printerGroupBox->setGeometry(20, 40, this->width() - 40, 60);

	this->printerName = new QLabel("Name:", this);
	this->printerName->setGeometry(40, 60, 40, 20);

	this->printerCombo = new QComboBox(this);
	this->printerCombo->setGeometry(100, 60, this->width() - 140, 20);
	this->printerCombo->setIconSize(QSize(17, 17));

	this->updatePrinterCombo();

	this->plotAreaGroupBox = new QGroupBox("Plot Area", this);
	this->plotAreaGroupBox->setGeometry(20, 110, this->width() - 200, 95);

	this->whatToPlotLabel = new QLabel("What to plot:", this);
	this->whatToPlotLabel->setGeometry(30, 135, 100, 20);

	this->whatToPlotCombo = new QComboBox(this);
	this->whatToPlotCombo->setGeometry(30, 160, 100, 20);

	this->windowButton = new QPushButton("Window <", this);
	this->windowButton->setGeometry(150, 158, 100, 25);
	this->windowButton->hide();

	this->updateWhatToPlotCombo();


	this->numberOfCopiesGroupBox = new QGroupBox("Number of copies", this);
	this->numberOfCopiesGroupBox->setGeometry(this->width() - 160, 110, 140, 60);

	this->numberSpinBox = new QSpinBox(this);
	this->numberSpinBox->setGeometry(this->width() - 100, 135, 40, 25);
	this->numberSpinBox->setMinimum(1);

	this->centerThePlotCheckBox = new QCheckBox("Center the plot", this);
	this->centerThePlotCheckBox->setGeometry(20, 205, 140, 25);

	this->pageSetupButton = new QPushButton("Page Setup", this);
	this->pageSetupButton->setGeometry(this->width() - 160, 180, 140, 25);

	this->okButton = new QPushButton("Ok", this);
	this->okButton->setGeometry(120, this->height() - 40, 100, 25);

	this->printButton = new QPushButton("Print", this);
	this->printButton->setGeometry(230, this->height() - 40, 100, 25);

	this->cancelButton = new QPushButton("Cancel", this);
	this->cancelButton->setGeometry(340, this->height() - 40, 100, 25);

	this->previewButton = new QPushButton("Preview", this);
	this->previewButton->setGeometry(10, this->height() - 40, 100, 25);

}

void ShPlotDialog::connectSignals() {

	connect(this->printButton, &QPushButton::released, this, &ShPlotDialog::printButtonClicked);
	connect(this->pageSetupButton, &QPushButton::released, this, &ShPlotDialog::pageSetupButtonClicked);
	connect(this->cancelButton, &QPushButton::released, this, &ShPlotDialog::cancelButtonClicked);
	connect(this->previewButton, &QPushButton::released, this, &ShPlotDialog::previewButtonClicked);
	connect(this->okButton, &QPushButton::released, this, &ShPlotDialog::okButtonClicked);
	connect(this->whatToPlotCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(whatToPlotIndexChanged(int)));
	connect(this->windowButton, &QPushButton::released, this, &ShPlotDialog::windowButtonClicked);
	
}

void ShPlotDialog::updatePrinterInfo() {

	ShPlotManager *manager = ShPlotManager::getInstance();
	QPrinter *printer = manager->getPrinter();

	printer->setCopyCount(1);

	this->centerThePlotCheckBox->setChecked(manager->isCenterThePlot());
	this->printerCombo->setCurrentIndex(this->printerCombo->findText(manager->getPrinterName()));
	this->whatToPlotCombo->setCurrentIndex(this->whatToPlotCombo->findText(manager->getWhatToPlotText()));
	this->windowPrevX = manager->getWindowPrevX();
	this->windowPrevY = manager->getWindowPrevY();
	this->windowCurrentX = manager->getWindowCurrentX();
	this->windowCurrentY = manager->getWindowCurrentY();

}

void ShPlotDialog::updateWhatToPlotCombo() {

	this->whatToPlotCombo->clear();

	this->whatToPlotCombo->addItem("Display");
	this->whatToPlotCombo->addItem("Window");
}

void ShPlotDialog::updatePrinterCombo() {

	this->printerCombo->clear();

	ShIcon icon(":/Image/File/Print.png");

	QStringList names = QPrinterInfo::availablePrinterNames();

	for (int i = 0; i < names.size(); i++) {

		this->printerCombo->addItem(icon, names[i]);

	}

	this->printerCombo->setCurrentIndex(this->printerCombo->findText(QPrinterInfo::defaultPrinterName()));

}


void ShPlotDialog::printButtonClicked() {

	ShPlotManager *plotManager = ShPlotManager::getInstance();
	ShCADWidget *widget = ShCADWidgetManager::getInstance()->getActivatedWidget();

	if (widget == nullptr)
		return;

	QPrinter *printer = plotManager->getPrinter();

	printer->setCopyCount(this->numberSpinBox->value());
	printer->setPrinterName(this->printerCombo->currentText());

	this->savePrinterInfo();



	QPainter painter(printer);
	double xscale, yscale, scale;
	QRect drawRect;
	QRect windowRect;

	if (plotManager->getWhatToPlot() == WhatToPlot::PlotDisplay) {

		windowRect = widget->rect();
	}
	else {

		windowRect = this->convertWindowRect(plotManager->getWindowPrevX(), plotManager->getWindowPrevY(),
			plotManager->getWindowCurrentX(), plotManager->getWindowCurrentY());
	}

	xscale = printer->pageRect().width() / double(windowRect.width());
	yscale = printer->pageRect().height() / double(windowRect.height());
	scale = qMin(xscale, yscale);

	if (plotManager->getWhatToPlot() == WhatToPlot::PlotWindow)
		painter.translate(-double(windowRect.topLeft().x())*scale, -double(windowRect.topLeft().y())*scale);


	drawRect = QRect(0, 0, double(windowRect.width())*scale, double(windowRect.height())*scale);

	if (plotManager->isCenterThePlot() == true) {

		if (drawRect.width() >= drawRect.height()) {

			painter.translate(0, printer->pageRect().height() / 2);
			painter.translate(0, -((double)(windowRect.height())*scale) / 2);

			drawRect = QRect(0, printer->pageRect().height() / 2 - (double(drawRect.height())) / 2,
				drawRect.width(), drawRect.height());

		}
		else {


			painter.translate(printer->pageRect().width() / 2, 0);
			painter.translate(-((double)(windowRect.width())*scale) / 2, 0);

			drawRect = QRect(printer->pageRect().width() / 2 - (double(drawRect.width())) / 2, 0,
				drawRect.width(), drawRect.height());

		}
	}


	widget->plot(&painter, scale);

	painter.resetTransform();


	QRect rect(QPoint(0, 0), QPoint(drawRect.topRight()));
	painter.eraseRect(rect);

	rect = QRect(QPoint(drawRect.bottomLeft()), QPoint(printer->pageRect().width(), printer->pageRect().height()));
	painter.eraseRect(rect);

	rect = QRect(QPoint(0, 0), QPoint(drawRect.bottomLeft()));
	painter.eraseRect(rect);

	rect = QRect(QPoint(drawRect.topRight()), QPoint(printer->pageRect().width(), printer->pageRect().height()));
	painter.eraseRect(rect);



	QPoint point, point2;

	point = QPoint(-printer->paperRect().width(), -printer->paperRect().height());
	point2 = QPoint(printer->paperRect().width(), 0);
	painter.eraseRect(QRect(point, point2));

	point2 = QPoint(0, printer->paperRect().height());
	painter.eraseRect(QRect(point, point2));

	point = QPoint(-100, printer->pageRect().height());
	point2 = QPoint(printer->paperRect().bottomRight().x(), printer->paperRect().bottomRight().y());
	painter.eraseRect(QRect(point, point2));

	point = QPoint(printer->pageRect().width(), 0);
	painter.eraseRect(QRect(point, point2));


	painter.end();

	this->close();

}

void ShPlotDialog::pageSetupButtonClicked() {

	ShPlotManager *manager = ShPlotManager::getInstance();
	QPrinter *printer = manager->getPrinter();

	QPageSetupDialog dlg(printer, this);
	dlg.exec();

}

void ShPlotDialog::cancelButtonClicked() {

	this->close();

}

void ShPlotDialog::okButtonClicked() {

	this->savePrinterInfo();

}


void ShPlotDialog::previewButtonClicked() {

	this->savePrinterInfo();

	ShPlotPreviewDialog preview(this);
	preview.exec();
}


void ShPlotDialog::whatToPlotIndexChanged(int index) {

	if (this->whatToPlotCombo->currentText() == "Window")
		this->windowButton->show();
	else
		this->windowButton->hide();

}


void ShPlotDialog::windowButtonClicked() {

	ShCADWidget *widget = ShCADWidgetManager::getInstance()->getActivatedWidget();

	if (widget == nullptr)
		return;

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionSelectPlotArea);
	widget->changeAction(strategy);

	ShSelectPlotAreaAction *action = dynamic_cast<ShSelectPlotAreaAction*>(widget->getCurrentAction());
	action->setPlotDialog(this);
	this->setVisible(false);
}



void ShPlotDialog::setWindowPrevXY(double windowPrevX, double windowPrevY) {

	this->windowPrevX = windowPrevX;
	this->windowPrevY = windowPrevY;

}

void ShPlotDialog::setWindowCurrentXY(double windowCurrentX, double windowCurrentY) {

	this->windowCurrentX = windowCurrentX;
	this->windowCurrentY = windowCurrentY;

}

QRect ShPlotDialog::convertWindowRect(double windowPrevX, double windowPrevY, double windowCurrentX, double windowCurrentY) {

	ShCADWidgetManager *manager = ShCADWidgetManager::getInstance();
	int prevX, prevY, currentX, currentY;

	ShCADWidget *widget = manager->getActivatedWidget();

	
	widget->convertEntityToDevice(windowPrevX, windowPrevY, prevX, prevY);
	widget->convertEntityToDevice(windowCurrentX, windowCurrentY, currentX, currentY);

	int width = abs(prevX - currentX);
	int height = abs(prevY - currentY);
	int topLeftX, topLeftY;

	if (prevX > currentX) {
		topLeftX = currentX;
	}
	else {
		topLeftX = prevX;
	}

	if (prevY > currentY) {
		topLeftY = currentY;
	}
	else {
		topLeftY = prevY;
	}

	return QRect(QPoint(topLeftX, topLeftY), QPoint(topLeftX + width, topLeftY + height));
}

void ShPlotDialog::savePrinterInfo() {

	ShPlotManager *manager = ShPlotManager::getInstance();

	manager->setIsSavedInfo(true);
	manager->setIsCenterThePlot(this->centerThePlotCheckBox->isChecked());
	manager->setPrinterName(this->printerCombo->currentText());
	manager->setWhatToPlot(this->whatToPlotCombo->currentText());
	manager->setWindowPrevXY(this->windowPrevX, this->windowPrevY);
	manager->setWindowCurrentXY(this->windowCurrentX, this->windowCurrentY);

}